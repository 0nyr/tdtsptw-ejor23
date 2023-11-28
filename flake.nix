{
  description = "A simple C++ project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs }: {
    devShell.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.mkShell {
      buildInputs = [
        nixpkgs.legacyPackages.x86_64-linux.gcc
        nixpkgs.legacyPackages.x86_64-linux.gnumake
        nixpkgs.legacyPackages.x86_64-linux.gdb
      ];

      shellHook = ''
        echo "Welcome to your C++ development environment"
      '';
    };
  };
}
