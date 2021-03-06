{ nixpkgs ? import <nixpkgs> {} }:
let
  inherit (nixpkgs) pkgs;
  packages = [ ];
  myTexLive = with pkgs; texlive.combine { inherit (texlive) scheme-full; };
in pkgs.stdenv.mkDerivation {
  name = "logic-latex";
  buildInputs = with pkgs; [ less man myTexLive gnumake dot2tex graphviz ] ++ packages;
}

