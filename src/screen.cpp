#include "LedControl.h"
#include "screen.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12, 10, 11, 1);

void clearScreen()
{
    lc.clearDisplay(0);
}

void initScreen()
{
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
    lc.shutdown(0, false);
    /* Set the brightness to a medium values */
    lc.setIntensity(0, 4);
    /* and clear the display */
    lc.clearDisplay(0);
}

void writeSkipping(byte *buf, int skip)
{
    for (int i = 0; i < 8 - skip; i++)
    {
        lc.setRow(0, i + skip, buf[i]);
    }
}

void write(byte *buf)
{
    writeSkipping(buf, 1);
}

void writeNegate(byte *buf)
{
    for (int i = 0; i < 7; i++)
    {
        if (i == 3)
        {
            lc.setRow(0, i + 1, buf[i] | B01100000);
        }
        else
        {
            lc.setRow(0, i + 1, buf[i]);
        }
    }
}