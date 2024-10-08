﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class ForwardList: IEnumerable
	{
		Element Head;
		public uint Size { get; private set; }
		public ForwardList()
		{
			Head = null;
			Console.WriteLine($"LConstructor:\t{GetHashCode()}");
			Size = 0;
		}
		
		~ForwardList()
		{
			Console.WriteLine($"LDestructor:\t{GetHashCode()}");
		}
		
		public void Clear()
		{
			while (Head != null)
			{
				pop_front();
			}
			Head = null;
		}
		//					Adding elements:
		/*public void push_front(int Data)
		{
			//1)создаем новый элемент:
			Element New = new Element(Data);
			//2)подключаем новый элемент у списку
			New.pNext = Head;
			//3)Смещаем голову на новый элемент
			Head = New;
			Size++;
		}*/

		//public void push_front(int Data) => Head = new Element(Data, Head);
		public void push_front(int Data)
		{
			Head = new Element(Data, Head);
			Size++;
		}
		public void push_back(int Data)
		{
			//if (Head == null) Head = new Element(Data);
			if (Head == null) push_front(Data);
			else
			{
				Element Temp = Head;
				while (Temp.pNext != null)
					Temp = Temp.pNext;
				Element New = new Element(Data);
				Temp.pNext = New;
				Size++;
			}
		}
		public void insert(int Data,int Index)
		{
			if (Index == 0)
			{
				push_front(Data);
				return;
			}
			if (Index > Size) return;
			else
			{
				Element Temp = Head;
				for (int i = 0; i < Index - 1; i++)
					if (Temp.pNext == null) break;
					else Temp = Temp.pNext;
				Element New = new Element(Data);
				New.pNext = Temp.pNext;
				Temp.pNext = New;
				Size++; 
			}
		}
		//removing elements:
		public void pop_front()
		{
			//Element erased = Head;	//Сохраняем адресс удаляемого элемента
			Head = Head.pNext;		//исключаем элемент из списка
			//erased.pNext = null;
			//erased = null;
			Size--;
		}
		public void pop_back()
		{
			if (Head == null) return;
			if (Head.pNext == null) { pop_front(); Size--; } 
            else
            {
            Element Temp = Head;
			while (Temp.pNext.pNext != null)
			{
				Temp = Temp.pNext;
			}
			Temp.pNext = null;
				Size--;
			}
		}
		//			Methods:
		public void Print()
		{
			Element Temp = Head;
			//Итератор-это указатель, при помощи которого можно получить доступ к элементам структуры данных
			while ( Temp != null )
			{
                Console.Write($"\t{Temp.Data}\t");
				Temp = Temp.pNext;
            }
            Console.WriteLine();
        }



		public void Add(int Data)
		{
			push_back(Data);
		}

		//public IEnumerator<int> GetEnumerator()
		//{
		//	Element Temp = Head;
		//	while (Temp != null)
		//	{
		//		yield return Temp.Data;
		//		Temp = Temp.pNext;
		//	}
		//}

		//IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
		IEnumerator IEnumerable.GetEnumerator() =>new Enumerator (Head);
		//IEnumerator IEnumerable.GetEnumerator()
		//{ return GetEnumerator(); }

		public void erase(int Index)
		{
			if (Index >= Size || Head == null)
			{
				Console.WriteLine("Некорректный индекс.");
				return;
			}

			if (Index == 0)
			{
				pop_front();
				return;
			}

			Element Temp = Head;
			for (int i = 0; i < Index - 1; i++)
				Temp = Temp.pNext;
			
			Temp.pNext = Temp.pNext.pNext;
			Size--;
		}


	}
}
