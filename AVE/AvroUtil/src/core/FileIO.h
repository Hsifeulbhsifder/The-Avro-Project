#ifndef AVRO_UTIL_FILE_IO_H
#define AVRO_UTIL_FILE_IO_H

#include "avro_typedefs.h"
//TODO: Scrap this system and rebuild allowing for asynchronous file IO
struct AvroFile{
	char* m_data;
};

struct AvroBinaryFile{
	U8* m_data;
};

typedef AvroFile AFile;
typedef AvroBinaryFile ABFile;


INLINEFORCE DLLEXPORT AFile ReadEntireFile(char* filepath);

INLINEFORCE DLLEXPORT B32 FlushToFile(char* filepath, AFile* file);

INLINEFORCE DLLEXPORT B32 AppendToFile(char* filepath, AFile* file);

INLINEFORCE DLLEXPORT B32 CreateNewFile(char* filepath, B32 overwriteExisting);

INLINEFORCE DLLEXPORT ABFile ReadBinaryFile(char* filepath);

INLINEFORCE DLLEXPORT B32 FlushToFile(char* filepath, ABFile* file);

#endif