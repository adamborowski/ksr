using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NETCOM;
namespace netklient1
{
    class Program
    {
        static void Main(string[] args)
        {
            Type t = Type.GetTypeFromProgID("KSR.Stos.2");
            object k = Activator.CreateInstance(t);
            t.InvokeMember("Push", System.Reflection.BindingFlags.InvokeMethod, null, k, new object[] { 1 });
            t.InvokeMember("Push", System.Reflection.BindingFlags.InvokeMethod, null, k, new object[] { 1 });
            object[] args2 = new object[] { null };
            t.InvokeMember("Pop", System.Reflection.BindingFlags.InvokeMethod,
             null, k, args2);
            Console.WriteLine("Pop = {0}", (int)args2[0]);
        }
    }
}
