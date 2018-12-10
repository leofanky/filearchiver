# SystemsProgramming-FileArchiver
Archives files within a system. Modified version of the unix tar command. Project for Systems Programming class.

# Flags
"-a": (Syntax: archiver -a archivename file1....fileN) This function creates an archive (archivename) of any amount of files (file1-fileN) by writing the files to a binary file.   
"-u": (Syntax: archiver -u archivename) This function unpacks the previously archived file, recreating each of the original files in the archive.   
"-l": (Syntax: archiver -l archivename) Prints the size of the archive, number of files in the archive, and each file name along with it's corresponding size.   
"-v": (Syntax: archiver -v archivename file1....fileN) Determines whether the archive (archivename) is damaged. Analyzes it in comparison to the files and prints a statement either stating it's correct, how many bytes it's missing, or whether the data is corrupted.   
