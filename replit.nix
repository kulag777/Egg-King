{ pkgs }: {
	deps = [
   pkgs.iproute
   pkgs.portmidi
   pkgs.pkg-config
   pkgs.libpng
   pkgs.libjpeg
   pkgs.freetype
   pkgs.fontconfig
   pkgs.SDL2_ttf
   pkgs.SDL2_mixer
   pkgs.SDL2_image
   pkgs.SDL2
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}