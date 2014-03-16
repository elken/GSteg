int encode(const char* iBmp, const char* oBmp, const char* txt)
{
    std::ifstream i(iBmp, std::ios::binary | std::ios::ate), t(txt, std::ios::ate);
    std::ofstream o(oBmp, std::ios::binary);

    if(o.bad() == true)
    {
        o << " " << std::endl;
        o.close();
    }
    
    if(i.is_open() && o.is_open() && t.is_open())
    {
        const std::streampos iSize = i.tellg();
        const std::streampos tSize = t.tellg();
        char* header = new char [54];
        char* eBuf = new char [sizeof(int(iSize)-54)];
        char* tBuf = new char [tSize];

        i.seekg(0, std::ios::beg);
        t.seekg(0, std::ios::beg);
        i.read(header, 54);
        i.seekg(54);
        i.read(eBuf, int(iSize)-54);
        t.read(tBuf, tSize);
        o.write(header, 54);
        o << char(3);
        o.write(tBuf, tSize);
        o << char(7);
        o.write(eBuf, sizeof(eBuf));
        return 0;
    }
    else
    {
        std::cerr << "I am error." << std::endl;
        return 1;
    }
}


int decode(const char* iBmp)
{
    std::ifstream i(iBmp, std::ios::binary | std::ios::ate);

    if(i.is_open())
    {
        std::streampos iSize = i.tellg();
        i.seekg(55);
        char* tBuf = new char[int(iSize)-54];

        for(int j=0;i.peek()!=char(7);j++)
        {
            tBuf[j] = i.get();
        }

        for(int k=0;k<(int(iSize)-54);k++)
        {
            std::cout << tBuf[k];
        }

        return 0;
    }
    else
    {
        std::cerr << "I am error." << std::endl;
        return 1;
    }
}
