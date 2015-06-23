#ifndef AVRO_UTIL_FILE_IO_H
#define AVRO_UTIL_FILE_IO_H

#include "avro_typedefs.h"

struct AvroFile{
	char* m_data;
};

struct AvroBinaryFile{
	U8* m_data;
};

typedef AvroFile AFile;
typedef AvroBinaryFile ABFile;


INLINEFORCE DLLEXPORT AFile ReadEntireFile(char* filepath);

INLINEFORCE DLLEXPORT B8 FlushToFile(char* filepath, AFile* file);

INLINEFORCE DLLEXPORT B8 AppendToFile(char* filepath, AFile* file);

INLINEFORCE DLLEXPORT B8 CreateNewFile(char* filepath, B8 overwriteExisting);

INLINEFORCE DLLEXPORT ABFile ReadBinaryFile(char* filepath);

INLINEFORCE DLLEXPORT B8 FlushToFile(char* filepath, ABFile* file);

#endif