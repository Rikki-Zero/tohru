{
  description = "Development environment with Clang, Bear, and Autotools";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.05";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in
      pkgs.mkShell {
        buildInputs = with pkgs; [
          xmake
          pkg-config
          clang-tools
          llvmPackages_18.clangUseLLVM
        ];
        shellHook = ''
          unset LD
        '';
      };
  };
}
