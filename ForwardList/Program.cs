//#define BASE_CHECK

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class Program
	{
		static void Main(string[] args)
		{
			Random random = new Random(0);
#if BASE_CHECK
			Console.WriteLine("Введите размер списка: ");
			int n = Convert.ToInt32(Console.ReadLine());
			ForwardList list = new ForwardList();
			for (int i = 0; i < n; i++)
			{
				list.push_back(random.Next(100));
			}
			//list.Print();
			//list.pop_back();
			//list.Print();
			//list.Clear();
			//list.Print();
			//list.push_back(Convert.ToInt32(999));
			//list.Print();
			Console.WriteLine("Введите индекс добавляемого элемента: ");
			int index = Convert.ToInt32(Console.ReadLine());
			Console.WriteLine("Введите значение добавляемого элемента: ");
			int value = Convert.ToInt32(Console.ReadLine());
			list.insert(value, index);
			list.Print(); 
#endif
			/*
			Console.WriteLine("Введите индекс удаляемого элемента: ");
			int Index = Convert.ToInt32(Console.ReadLine());
			list.Print();
			list.erase(Index);
			list.Print();
			*/
			ForwardList list1 = new ForwardList() { 3, 5, 8, 13, 21 };
			foreach (int i in list1)
			{
				Console.Write(i + "\t");
			}
			//list1.Print();
			Console.WriteLine();
		}
	}
}
