#include "pch.h"
#include "ResultWriter.h"
#include "config.h"
#include <string>

#pragma warning(disable:4996)

ResultWriter::ResultWriter():pFile(NULL)
{
    pFile = fopen(DEFAULT_RESULT_PATH, "w"); //新建文件
}

ResultWriter::ResultWriter(const char * path)
{
    char resultPath[200] = {0};
    strcat(resultPath, path);
    strcat(resultPath, "result.txt");
    pFile = fopen(resultPath, "w"); //新建文件
}

ResultWriter::~ResultWriter()
{
    close();
}

ResultWriter& ResultWriter::writeLine(const char* result)
{
    fprintf(pFile, "%s\n", result);
    fflush(pFile);
    return *this;
}

ResultWriter& ResultWriter::write(const char* result)
{
    fprintf(pFile, "%s", result);
    fflush(pFile);
    return *this;
}

void ResultWriter::close()
{
    if (pFile != NULL) {
        fclose(pFile);
        pFile = NULL;
    }
}
