using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HashTrash
{
    class Program
    {
        static void Main(string[] args)
        {
            List<uint> X = new List<uint>();
            RandomFillArray(20, X);
            List<uint> Y = new List<uint>();
            FillArray(Y, X);

            List<uint> X_ = new List<uint>(X);
            ChangeArray(X_);
            List<uint> Y_ = new List<uint>();
            FillArray(Y_, X_);

            Console.WriteLine("=================================================");
            PrintInfo(X, Y, "X");
            Console.WriteLine();
            PrintInfo(X_, Y_, "Y");
            Console.WriteLine("=================================================");
            Console.WriteLine("Correlation coefficient(X, HASH X): " + ComputeCoeff(X, Y));
            Console.WriteLine("Correlation coefficient (Y, HASH Y): " + ComputeCoeff(X_, Y_));
            Console.WriteLine("Correlation coefficient (HASH X, HASH Y): " + ComputeCoeff(Y, Y_));
            Console.WriteLine("Correlation coefficient (X, Y): " + ComputeCoeff(X, X_));

            CheckGroupCollision(Y, Y_);
            CheckCollision(Y, "H(x)");
            CheckCollision(Y_, "H(y)");
        }

        static void PrintInfo(List<uint> l1, List<uint> l2, string label)
        {
            Console.WriteLine($"{label}:");
            Console.WriteLine();
            for (int i = 0; i < l1.Count; i++)
            {
                string binary = Convert.ToString(l1[i], 2);
                Console.WriteLine(l1[i] + "\t   " + binary.PadLeft(20, '0') + "\t   H(x)=   \t" + l2[i]);
            }
        }

        static void RandomFillArray(uint count, List<uint> array)
        {
            Random randNum = new Random();
            for (uint i = 0; i < count; i++)
            {
                array.Add((uint)randNum.Next(0, (int)Pow(2, 20)));
            }
        }
        static void ChangeArray(List<uint> array)
        {
            for (int i = 0; i < array.Count; i++)
            {
                array[i] = (uint)(array[i] ^ 1 << i);
            }
        }
        static List<int> ConvertArray(List<uint> array)
        {
            List<int> l = new List<int>();
            for (int i = 0; i < array.Count; i++)
            {
                l.Add(Convert.ToInt32(array[i]));
            }

            return l;
        }

        static void PrintArray(List<int> array)
        {
            foreach (var item in array)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();
            Console.WriteLine();
        }

        static void FillArray(List<uint> array1, List<uint> array2)
        {
            uint n = Pow(2, 8 - 1 );
            foreach (var item in array2)
            {
                array1.Add(GetHash(item, n));
            }
        }

        static uint Pow(uint d1, uint d2)
        {
            uint powered = 1;
            for (int i = 0; i < d2; ++i)
            {
                powered *= d1;
            }
            return powered;
        }

        static uint GetHash(uint x, uint n, uint a = 251)
        {
            return Pow(a, x) % n;
        }

        static double ComputeCoeff(List<uint> l1, List<uint> l2)
        {
            List<int> values1 = ConvertArray(l1);
            List<int> values2 = ConvertArray(l2);

            if (values1.Count != values2.Count)
                return 9999999999999999999;

            var avg1 = values1.Average();
            var avg2 = values2.Average();

            var sum1 = values1.Zip(values2, (x1, y1) => (x1 - avg1) * (y1 - avg2)).Sum();

            var sumSqr1 = values1.Sum(x => Math.Pow((x - avg1), 2.0));
            var sumSqr2 = values2.Sum(y => Math.Pow((y - avg2), 2.0));

            var result = sum1 / Math.Sqrt(sumSqr1 * sumSqr2);

            return result;
        }

        static public void CheckGroupCollision(List<uint> ar1, List<uint> ar2)
        {
            int count = 0;
            Console.WriteLine("Group Collision");
            for (int i = 0; i < ar1.Count; i++)
            {
                if (ar1[i] == ar2[i]) count++;
            }
            Console.WriteLine("All count collision in H(x) and H(y) " + count + " times");
        }

        static public void CheckCollision(List<uint> ar1, string label)
        {
            uint count = 0;
            Dictionary<uint, uint> col = new Dictionary<uint, uint>();
            Console.WriteLine("Collision");
            for (int i = 0; i < ar1.Count; i++)
            {   if(col.ContainsKey(ar1[i]))
                {
                    col[ar1[i]]++;
                }
                else
                {
                    col[ar1[i]] = 1;
                }
            }

            foreach (KeyValuePair<uint, uint> keyValue in col)
            {
                if(keyValue.Value > 1)
                {
                    Console.WriteLine(keyValue.Key + " repeated " + keyValue.Value + " times");
                    count += keyValue.Value;
                }
            }
            Console.WriteLine("All count collision in " + label+ "  " + count + " times");
        }
    }
}
