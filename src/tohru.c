#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "../kobayashi-std/kobayashi.h"

#define VERSION_FILE_DIR "./defs/"
#define MAIN_FILE "v-c.txt"
#define MAX_BUFFER_SIZE 1024

// 全局变量，用于存储版本信息
k_dynamicArray *versions = NULL;

// 版本信息结构体
typedef struct
{
    int id;
    char *description;
    char *content; // 存储文件内容
    k_int64 timestamp;
} Version;

// 辅助函数：读取文件内容
char *readFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, file);
    fclose(file);
    string[fsize] = '\0';
    return string;
}

// 辅助函数：写入文件内容
void writeFile(const char *filename, const char *content)
{
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        fprintf(file, "%s", content);
        fclose(file);
    }
    else
    {
        perror("Error opening file for writing");
    }
}

// 辅助函数：生成版本文件名
char *generateVersionFilename(int versionId)
{
    char *filename = malloc(strlen(VERSION_FILE_DIR) + 20); // 预留足够空间
    sprintf(filename, "%s%d.txt", VERSION_FILE_DIR, versionId);
    return filename;
}

// 辅助函数：创建 defs 目录
void ensureDefsDirExists()
{
    struct stat st;
    if (stat(VERSION_FILE_DIR, &st) != 0)
    {
        if (mkdir(VERSION_FILE_DIR, 0777) != 0)
        {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
    }
}

// 初始化版本信息
void initVersionControl()
{
    versions = k_dynamicArray_init(10);
    ensureDefsDirExists();
}

// 释放版本信息
void releaseVersionControl()
{
    if (versions)
    {
        for (size_t i = 0; i < k_dynamicArray_size(versions); ++i)
        {
            Version *v = (Version *)k_dynamicArray_get(versions, i);
            if (v)
            {
                free(v->description);
                free(v->content);
            }
        }
        k_dynamicArray_destroy(versions);
        versions = NULL;
    }
}


// 辅助函数：将字符串分割成行
char **splitIntoLines(const char *content, int *lineCount) {
    if (content == NULL) {
        *lineCount = 0;
        return NULL;
    }

    int count = 1;
    const char *p = content;
    while (*p != '\0') {
        if (*p == '\n') {
            count++;
        }
        p++;
    }

    char **lines = (char **)malloc(sizeof(char *) * count);
    if (!lines) {
        perror("Failed to allocate memory for lines");
        *lineCount = 0;
        return NULL;
    }

    int i = 0;
    const char *start = content;
    p = content;
    while (*p != '\0') {
        if (*p == '\n') {
            int len = p - start;
            lines[i] = (char *)malloc(len + 1);
            if (!lines[i]) {
                perror("Failed to allocate memory for line");
                // 清理已分配的内存
                for (int j = 0; j < i; j++) {
                    free(lines[j]);
                }
                free(lines);
                *lineCount = 0;
                return NULL;
            }
            strncpy(lines[i], start, len);
            lines[i][len] = '\0';
            start = p + 1;
            i++;
        }
        p++;
    }

    // 处理最后一行没有换行符的情况
    if (start < p) {
        int len = p - start;
        lines[i] = (char *)malloc(len + 1);
        if (!lines[i]) {
            perror("Failed to allocate memory for last line");
            // 清理已分配的内存
            for (int j = 0; j < i; j++) {
                free(lines[j]);
            }
            free(lines);
            *lineCount = 0;
            return NULL;
        }
        strncpy(lines[i], start, len);
        lines[i][len] = '\0';
        i++;
    }

    *lineCount = i;
    return lines;
}

char *generateDiff(const char *prevContent, const char *currentContent) {
    char *diff = malloc(MAX_BUFFER_SIZE * 10); // 预留足够空间
    if (!diff) {
        perror("Failed to allocate memory for diff");
        return NULL;
    }
    diff[0] = '\0'; // 初始化为空字符串

    int prevLineCount = 0;
    char **prevLines = splitIntoLines(prevContent, &prevLineCount);

    int currentLineCount = 0;
    char **currentLines = splitIntoLines(currentContent, &currentLineCount);

    int i = 0, j = 0;
    while (i < prevLineCount || j < currentLineCount) {
        if (i < prevLineCount && j < currentLineCount && strcmp(prevLines[i], currentLines[j]) == 0) {
            strcat(diff, prevLines[i]);
            strcat(diff, "\n");
            i++;
            j++;
        } else if (i < prevLineCount && (j >= currentLineCount || (j < currentLineCount && (i + 1 >= prevLineCount || strcmp(prevLines[i+1], currentLines[j]) != 0)))) {
            strcat(diff, "- ");
            strcat(diff, prevLines[i]);
            strcat(diff, "\n");
            i++;
        } else if (j < currentLineCount) {
            strcat(diff, "+ ");
            strcat(diff, currentLines[j]);
            strcat(diff, "\n");
            j++;
        }
    }

    // 释放内存
    for (int k = 0; k < prevLineCount; k++) {
        free(prevLines[k]);
    }
    free(prevLines);

    for (int k = 0; k < currentLineCount; k++) {
        free(currentLines[k]);
    }
    free(currentLines);

    return diff;
}

// 生成 diff 信息
// char *generateDiff(const char *prevContent, const char *currentContent)
// {
//     char *diff = malloc(MAX_BUFFER_SIZE * 10); // 预留足够空间
//     if (!diff)
//     {
//         perror("Failed to allocate memory for diff");
//         return NULL;
//     }
//     diff[0] = '\0'; // 初始化为空字符串

//     if (prevContent == NULL)
//     {
//         char *add_line = malloc(MAX_BUFFER_SIZE);
//         if (currentContent != NULL && strlen(currentContent) > 0)
//         {
//             const char *current_ptr = currentContent;
//             while (*current_ptr != '\0')
//             {
//                 int len = 0;
//                 const char *start = current_ptr;
//                 while (*current_ptr != '\n' && *current_ptr != '\0')
//                 {
//                     len++;
//                     current_ptr++;
//                 }

//                 strncpy(add_line, start, len);
//                 add_line[len] = '\0';
//                 strcat(diff, "+ ");
//                 strcat(diff, add_line);
//                 strcat(diff, "\n");
//                 if (*current_ptr == '\n')
//                 {
//                     current_ptr++;
//                 }
//             }
//         }
//         free(add_line);
//         return diff;
//     }

//     const char *prev_ptr = prevContent;
//     const char *current_ptr = currentContent;

//     char *prev_line = malloc(MAX_BUFFER_SIZE);
//     char *current_line = malloc(MAX_BUFFER_SIZE);

//     while (1)
//     {
//         int prev_len = 0;
//         int current_len = 0;
//         const char *prev_line_start = prev_ptr;
//         const char *current_line_start = current_ptr;

//         // 读取当前行
//         while (*prev_ptr != '\n' && *prev_ptr != '\0')
//         {
//             prev_len++;
//             prev_ptr++;
//         }
//         while (*current_ptr != '\n' && *current_ptr != '\0')
//         {
//             current_len++;
//             current_ptr++;
//         }

//         strncpy(prev_line, prev_line_start, prev_len);
//         prev_line[prev_len] = '\0';
//         strncpy(current_line, current_line_start, current_len);
//         current_line[current_len] = '\0';

//         if (prev_len == 0 && current_len == 0)
//         {
//             break; // 都结束了
//         }
//         else if (prev_len == 0)
//         {
//             strcat(diff, "+ ");
//             strcat(diff, current_line);
//             strcat(diff, "\n");
//             if (*current_ptr == '\n')
//             {
//                 current_ptr++;
//             }
//         }
//         else if (current_len == 0)
//         {
//             strcat(diff, "- ");
//             strcat(diff, prev_line);
//             strcat(diff, "\n");
//             if (*prev_ptr == '\n')
//             {
//                 prev_ptr++;
//             }
//         }
//         else if (strcmp(prev_line, current_line) != 0)
//         {
//             strcat(diff, "- ");
//             strcat(diff, prev_line);
//             strcat(diff, "\n");
//             strcat(diff, "+ ");
//             strcat(diff, current_line);
//             strcat(diff, "\n");

//             if (*prev_ptr == '\n')
//             {
//                 prev_ptr++;
//             }
//             if (*current_ptr == '\n')
//             {
//                 current_ptr++;
//             }
//         }
//         else
//         {
//             if (*prev_ptr == '\n')
//             {
//                 prev_ptr++;
//             }
//             if (*current_ptr == '\n')
//             {
//                 current_ptr++;
//             }
//         }
//     }
//     free(prev_line);
//     free(current_line);
//     return diff;
// }

void printVersionList()
{
    for (int i = 0; i < k_dynamicArray_size(versions); i++)
    {
        k_valueType *item = k_dynamicArray_get(versions, i);
        Version *v = (Version *)k_valueType_get_ptr(item);
        printf("id: %d\nmsg: %s\n-----\n%s", v->id, v->description, v->content);
    }
}

// 提交新版本
void commitChanges()
{
    char choice;
    printf("> 你需要提交现在的文本内容作为一个新版本么？[Y/N]\n");
    scanf(" %c", &choice);
    if (choice != 'Y' && choice != 'y')
    {
        return;
    }

    // 获取当前时间戳
    time_t now;
    time(&now);

    // 读取当前文件内容
    char *currentContent = readFile(MAIN_FILE);
    if (currentContent == NULL)
    {
        currentContent = strdup("");
    }

    char desc_choice;
    char *description = NULL;
    printf("> 你需要记录一段备注么 [Y/N]\n");
    scanf(" %c", &desc_choice);
    if (desc_choice == 'Y' || desc_choice == 'y')
    {
        description = malloc(MAX_BUFFER_SIZE);
        printf("> 请输入备注：\n");
        // 使用 scanf 读取一行，防止空格
        scanf(" %s[^\n]", description);
    }
    else
    {
        description = strdup("(没有备注)");
    }

    // 创建新的版本信息
    Version* newVersion = (Version*)malloc(sizeof(Version));
    newVersion->id = k_dynamicArray_size(versions) + 1;
    newVersion->description = description;
    newVersion->content = currentContent;
    newVersion->timestamp = (k_int64)now;

    // 存储版本信息
    k_valueType v;
    k_valueType_init(&v, k_ptr_t);
    k_valueType_set_ptr(&v, newVersion);
    k_dynamicArray_add(versions, v);

    // 获取上一个版本的 content
    char *prevContent = NULL;
    if (k_dynamicArray_size(versions) > 1)
    {
        k_valueType *prev_v =
            k_dynamicArray_get(versions, k_dynamicArray_size(versions) - 2);
        Version *prevVersion = (Version *)k_valueType_get_ptr(prev_v);
        prevContent = prevVersion->content;
    }

    // 生成 diff 信息
    char *diff = generateDiff(prevContent, currentContent);

    // 保存版本文件
    char *versionFilename = generateVersionFilename(newVersion->id);
    // 创建版本描述文件内容
    char *fileContent = malloc(MAX_BUFFER_SIZE * 10);
    sprintf(fileContent, "id: %d\nmsg: %s\n-----\n%s", newVersion->id,
            newVersion->description, diff == NULL ? "" : diff);
    writeFile(versionFilename, fileContent);
    free(versionFilename);
    free(fileContent);
    free(diff);

    printf("----\n");

    //printVersionList();
}

// 查看版本记录
void viewVersions()
{
    printf("> 这里是目前所有的版本记录\n");
    printf("  ID  备注\n");
    for (size_t i = 0; i < k_dynamicArray_size(versions); i++)
    {
        k_valueType *v = k_dynamicArray_get(versions, i);
        Version *version = (Version *)k_valueType_get_ptr(v);
        printf("  %d   %s\n", version->id, version->description);
    }
    printf("\n");

    char choice;
    printf("> 需要查看某个版本么？[Y/N]\n");
    scanf(" %c", &choice);
    if (choice != 'Y' && choice != 'y')
    {
        return;
    }

    int versionId;
    printf("> 输入ID：");
    scanf(" %d", &versionId);

    for (size_t i = 0; i < k_dynamicArray_size(versions); i++)
    {
        k_valueType *v = k_dynamicArray_get(versions, i);
        Version *version = (Version *)k_valueType_get_ptr(v);
        if (version->id == versionId)
        {
            // 读取并打印版本描述文件
            char *versionFilename = generateVersionFilename(versionId);
            char *fileContent = readFile(versionFilename);
            if (fileContent != NULL)
            {
                printf("%s\n", fileContent);
                free(fileContent);
            }
            free(versionFilename);
        }
    }
}

// 回退版本
void rollbackVersion()
{
    char choice;
    printf("> 你需要回退版本么？[Y/N]\n");
    scanf(" %c", &choice);
    if (choice != 'Y' && choice != 'y')
    {
        return;
    }

    int targetVersionId;
    printf("> 输入需要回退的版本：");
    scanf(" %d", &targetVersionId);

    char confirmChoice;
    printf("> 再次确认，您需要回退么？[Y/N]\n");
    printf("> 回退以后会删除该状态之后的版本记录，该操作不可逆！\n");
    scanf(" %c", &confirmChoice);
    if (confirmChoice != 'Y' && confirmChoice != 'y')
    {
        return;
    }

    // 找到目标版本
    Version *targetVersion = NULL;
    size_t targetIndex = -1;
    for (size_t i = 0; i < k_dynamicArray_size(versions); ++i)
    {
        k_valueType *v = k_dynamicArray_get(versions, i);
        Version *version = (Version *)k_valueType_get_ptr(v);
        if (version->id == targetVersionId)
        {
            targetVersion = version;
            targetIndex = i;
            break;
        }
    }

    if (targetVersion == NULL)
    {
        printf("> 没有找到版本号\n");
        return;
    }

    // 写入内容
    writeFile(MAIN_FILE, targetVersion->content);

    // 清除版本
    while (k_dynamicArray_size(versions) > targetIndex + 1)
    {
        k_dynamicArray_remove(versions, k_dynamicArray_size(versions) - 1);
    }

    printf("> 已经将文件回退至选择的版本\n");
}

// 清除版本管理记录
void clearVersionHistory()
{
    char choice;
    printf("> 你需要清除版本管理记录么？[Y/N]\n");
    scanf(" %c", &choice);
    if (choice != 'Y' && choice != 'y')
    {
        return;
    }

    char confirmChoice;
    printf("> 再次确认，您需要清除版本管理记录么？[Y/N]\n");
    printf("> 清除版本管理记录以后会删除所有版本记录，该操作不可逆！\n");
    scanf(" %c", &confirmChoice);
    if (confirmChoice != 'Y' && confirmChoice != 'y')
    {
        return;
    }

    releaseVersionControl();
    initVersionControl();

    // 清理 defs 文件
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(VERSION_FILE_DIR)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                char *fullPath =
                    malloc(strlen(VERSION_FILE_DIR) + strlen(ent->d_name) + 1);
                sprintf(fullPath, "%s%s", VERSION_FILE_DIR, ent->d_name);
                remove(fullPath);
                free(fullPath);
            }
        }
        closedir(dir);
    }
    else
    {
        perror("Could not open directory");
        return;
    }

    printf("> 已经清除版本管理记录\n");
}

int main()
{
    initVersionControl();

    while (1)
    {
        printf("[版本管理系统]\n");
        printf("1. 提交更新\n");
        printf("2. 查看版本\n");
        printf("3. 回退版本\n");
        printf("4. 清除版本管理记录\n");
        printf("5. 退出\n");

        int operation;
        printf("> 请输入操作：\n");
        scanf(" %d", &operation);

        switch (operation)
        {
            case 1: commitChanges(); break;
            case 2: viewVersions(); break;
            case 3: rollbackVersion(); break;
            case 4: clearVersionHistory(); break;
            case 5: break;
            default: printf("> 输入错误，请重新输入！\n"); break;
        }
    }

    releaseVersionControl();

    return 0;
}