using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class Element
	{
		public int Data { get; set; }		//значение элемента
		public Element pNext { get; set; }  //Следующий элемент
		public Element(int data, Element pNext = null)
		{
			this.Data = data;
			this.pNext = pNext;
            Console.WriteLine($"EConstructor:\t{GetHashCode()}");
        }

		~Element() 
		{ 
            Console.WriteLine($"EDestructor:\t{GetHashCode()}");
		}

	}
}
