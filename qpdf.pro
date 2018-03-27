TEMPLATE = subdirs

SUBDIRS = qpdflib\
          pdfviewer \
        stalking

pdfviewer.depends = qpdflib
