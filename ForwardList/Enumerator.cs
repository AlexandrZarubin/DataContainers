using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class Enumerator<T> : IEnumerator
	{
		Element<T> Head {  get; set; }
		public Element<T> Temp { get; set; }
		//public Enumerator (Element temp=null)
		//{
		//	this.Temp = temp;
		//  Console.WriteLine($"EnumConstructor:\t{GetHashCode()}");
		//}
		public Enumerator(Element<T> Head = null)
		{
			this.Head = Head;
			this.Temp = null;
		}
		~Enumerator() { Console.WriteLine($"EnumDestructor:\t{GetHashCode()}"); }
		public object Current { get => Temp.Data; }
		public bool MoveNext()
		{
			Temp = Temp == null ? Head : Temp.pNext;
			//if (Temp == null) Temp = Head;
			//else Temp = Temp.pNext;
			return Temp != null;

		}
		public void Reset() { }

	}
}
