    {
        return O_WRONLY;
    }
    else
    {
        return -1;
    }
}
void load_file(int file, int position, int user_action)
{
    int number_of_butes = 256;
    int seek_type;
    switch (user_action)
    {
    case 1:
        seek_type = SEEK_SET;
        break;
    case 2:
        seek_type = SEEK_CUR;
        break;
    case 3:
        seek_type = SEEK_END;
        break;