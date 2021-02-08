
#include <cstdio>
#include <ScreenUtils/ScreenFloatDisplay.h>

using namespace std;
using namespace irr;
using namespace IOSP;

void printLineInfo(const ScaleFloatDisplay& d, int line)
{
    printf("%4i %7.2f      %4i     %4i    %7.2f   %7.2f    %7.2f\n",
        line,
        d.getLineValue(line),
        d.getRelativeLinePosition(line),
        d.getAbsoluteLinePosition(line),
        d.getLineNumberFromValue(d.getLineValue(line)),
        d.getLineNumberFromRelativePosition(d.getRelativeLinePosition(line)),
        d.getLineNumberFromAbsolutePosition(d.getAbsoluteLinePosition(line))
    );
}

int main()
{
    ScaleFloatDisplay display;
    display.setValueScale(10);
    display.setValueShift(0);
    display.setVisualScale(2);
    display.setValue(1);
    display.getBase().UpperLeftCorner.Y = 10;
    display.getBase().LowerRightCorner.Y = 20;
    
    puts("Line   Value   rel-pos. abs-pos. |  r-val. r-rel-pos. r-abs-pos.");
    for (int i = 2; i >= -2; i--)
        printLineInfo(display, i);
    display.getBase().UpperLeftCorner.Y = 250;
    display.getBase().LowerRightCorner.Y = 350;
    display.setValueScale(2);
    display.setVisualScale(1);
    display.setValue(0);
    int top = display.getInner().UpperLeftCorner.Y;
    int line = display.getLineNumberFromAbsolutePosition(top);
    printLineInfo(display, -125);
    printf("Top: %i (%i), line: %i\n", top, display.getRelativeFromAbsolutePosition(top), line);
    printLineInfo(display, line);
    
    return 0;
}
