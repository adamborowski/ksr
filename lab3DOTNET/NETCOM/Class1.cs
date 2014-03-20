using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Reflection;


[Guid("E728F9D2-E2D0-47ED-8A7E-E7EC5357CFB0"),
 ComVisible(true),
 ClassInterface(ClassInterfaceType.None),
 ProgId("KSR.Stos.2")]
public class Stos : NETCOM.IStos
{
    public Stos() { }
    private uint stackLength = 0;
    public uint Push(int v)
    {
        stackLength++;
        return 0;
    }
    public uint Pop(out int v)
    {
        stackLength--;
        v = (int)stackLength;
        return 0;
    }

}