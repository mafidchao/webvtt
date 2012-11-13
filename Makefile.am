ACLOCAL_AMFLAGS = -I build/autoconf
SUBDIRS = src include
BUILT_SOURCES = ${top_builddir}/include/webvtt/webvtt-config.h
${top_builddir}/include/webvtt/webvtt-config.h: ${top_builddir}/config.h
	@cat $< | sed "s/#define \([[:alpha:]_]\{1,\}\)/#define WEBVTT_\1/" > $@
