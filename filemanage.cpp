unsigned long get_file_size(const string & path, const string & filename)
{
	string fullpath = path+filename;
    unsigned long filesize = -1;
    struct stat statbuff;
    if (stat(fullpath.c_str(), &statbuff) < 0)
    {
        return filesize;
    }else{
        filesize = statbuff.st_size;
    }
    return filesize;
}