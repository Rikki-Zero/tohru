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
        buildInputs = [
          pkgs.clang
          pkgs.bear
          pkgs.autoconf
          pkgs.automake
          pkgs.libtool
          pkgs.make
          pkgs.gcc
          pkgs.git
        ];
        shellHook = ''
        '';
      };
  };
}
