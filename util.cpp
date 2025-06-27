namespace stUTIL
{
    /* Converts int to binary array for further processing */
    void intToBinaryArray(int number, int binaryArray[8])
    {
        for (int i = 7; i >= 0; --i)
        {
            int bit = (number >> i) & 1;
            binaryArray[7 - i] = bit;
        }
    }
}