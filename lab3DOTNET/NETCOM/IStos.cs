using System;
using System.Runtime.InteropServices;
using System.Reflection;

namespace NETCOM
{
    [Guid("ABCDEFAA-E2D0-47ED-8A7E-E7EC5357CFB0"),
    ComVisible(true),
    InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface IStos
    {
        uint Pop(out int v);
        uint Push(int v);
    }
}
