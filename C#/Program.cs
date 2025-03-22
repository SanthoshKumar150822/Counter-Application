using System;

namespace CounterApplication
{
    class CounterApp
    {
        public static void Main(string[] args)
        {
            int choice = 0, counter1=0, counter2=0, counter3=0, counter4=0, currentToken=0, token=0;
            while(1>0)
            {
                Console.WriteLine("Enter 1 for Window Operator1");
                Console.WriteLine("Enter 2 for Window Operator2");
                Console.WriteLine("Enter 3 for Window Operator3");
                Console.WriteLine("Enter 4 for Window Operator4");
                Console.WriteLine("Enter 5 for get a token for access to a Window Operator.\n");
                Console.Write("Enter your choice:");
                choice = Convert.ToInt32(Console.ReadLine());

                // Validate user input
                while (choice<0 || choice>5)
                {
                    Console.Write("Enter your choice:");
                    choice = Convert.ToInt32(Console.ReadLine());
                }


                switch (choice)
                {
                    case 1:
                        if (token > 0 && currentToken < token)
                        {
                            currentToken++;
                            counter1=currentToken;
                        }
                        break;

                    case 2:
                        if (token > 0 && currentToken < token)
                        {
                            currentToken++;
                            counter2 = currentToken;
                        }
                        break;

                    case 3:
                        if (token > 0 && currentToken < token)
                        {
                            currentToken++;
                            counter3 = currentToken;
                        }
                        break;

                    case 4:
                        if (token > 0 && currentToken < token)
                        {
                            currentToken++;
                            counter4 = currentToken;
                        }
                        break;

                    case 5:
                         token++;
                        Console.WriteLine("Your Token number is " + token);
                        break;
                }

                // Display current state of counters
                Console.WriteLine("\nCounter1:" + counter1+"\t\t\tCounter2:"+counter2);
                Console.WriteLine("Counter3:" + counter3 + "\t\t\tCounter4:" + counter4+"\n");
            }

        }
    }
}