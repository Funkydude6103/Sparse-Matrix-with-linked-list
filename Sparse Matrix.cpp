#include<iostream>
#include<vector>
#include <string> // For String Function
#include <cctype> // For changing upper to lower
#include <conio.h>
#include<cmath>
#include<fstream>
using namespace std;
class SparseMatrix {
	struct Node {
		int value;
		int col_index;
		Node* Next_in_Row;
		Node(int v)
		{
			value = v;
			Next_in_Row = NULL;
			col_index = 0;
		};
		Node()
		{
			value = 0;
			Next_in_Row = NULL;
			col_index = 0;
		}
	};
	//Dimensions
	int M;
	int N;
	vector<Node*> Row_List;
	void add(Node* head, Node* b)
	{
		Node* temp = head;
		while (temp->Next_in_Row != NULL)
		{
			temp = temp->Next_in_Row;
		}
		temp->Next_in_Row = b;
	}
public:
	
	SparseMatrix()
	{
		N = 0;
		M = 0;

	}
	SparseMatrix(string file_name)
	{
		Read(file_name);
	}
	void Read(string file_name)
	{
		ifstream fin;
		fin.open(file_name);
		if (fin.is_open())
		{
			//Finding number of columns
			double count = 0;
			while (!fin.eof())
			{
				char a;
				a = fin.get();
				if (a == '\n')
				{
					break;
				}
				count++;
			}
			N = ceil( count / 2);

			fin.close();
			//Finding number of rows
			int count2=0;
			fin.open(file_name);
			while (!fin.eof())
			{
				string a;
				getline(fin,a);
				count2++;
			}
			M = count2;
			fin.close();

			//Making the row List
			for (int i=1;i<=M;i++)
			{
				Node* temp = new Node(i);
				temp->Next_in_Row = NULL;
				temp->col_index = 0;
				Row_List.push_back(temp);
			}

			//Making Colums
			fin.open(file_name);
			for(int i=0;i<M;i++)
			for (int j = 1; j <= N; j++)
			{
				int k;
				fin >> k;
				if (k != 0)
				{
					Node* temp2 = new Node(k);
					temp2->col_index = j;
					temp2->Next_in_Row = NULL;
					add(Row_List[i], temp2);

				}
			}
		}
		else
		{
			cout << "Error opening file : " << file_name;
		}

	}
	void print()
	{
		for (int i = 0; i < M; i++)
		{
			int count = 0;
			Node* temp = Row_List[i]->Next_in_Row;
			for (int k=0; temp!=NULL;temp=temp->Next_in_Row)
			{
				int j = temp->col_index;
				for (int l = 0; l < j - k - 1; l++)
				{
					cout << 0 <<" ";
					count++;

				}
				cout<< temp->value<<" ";
				k = j;
				count++;
			}
			for (int i = 0; i < N-count; i++)
			{
				cout << 0<<" ";
			}
			cout << endl;
		}

	}
	SparseMatrix(const SparseMatrix& obj)
	{
		N = obj.N;
		M = obj.M;
		//Making the row List
		int j = 0;
		for (int i = 1; i <= M; i++,j++)
		{
			Node* temp = new Node(i);
			temp->Next_in_Row = NULL;
			temp->col_index = 0;
			Row_List.push_back(temp);

			Node* temp2 =obj.Row_List[j]->Next_in_Row;
			if (temp2 != NULL)
			{
				while (temp2 != NULL)
				{
					Node* temp3 = new Node(temp2->value);
					temp3->col_index = temp2->col_index;
					add(Row_List[j], temp3);
					temp2 = temp2->Next_in_Row;

				}
			}
			else
			{
				Row_List[j]->Next_in_Row = NULL;
			}
		}
		
	}
	const SparseMatrix& operator = (const SparseMatrix& obj)
	{
		Row_List.clear();
		N = obj.N;
		M = obj.M;
		//Making the row List
		int j = 0;
		for (int i = 1; i <= M; i++, j++)
		{
			Node* temp = new Node(i);
			temp->Next_in_Row = NULL;
			temp->col_index = 0;
			Row_List.push_back(temp);

			Node* temp2 = obj.Row_List[j]->Next_in_Row;
			if (temp2 != NULL)
			{
				while (temp2 != NULL)
				{
					Node* temp3 = new Node(temp2->value);
					temp3->col_index = temp2->col_index;
					add(Row_List[j], temp3);
					temp2 = temp2->Next_in_Row;

				}
			}
			else
			{
				Row_List[j]->Next_in_Row = NULL;
			}
		}
		return *this;
	}
	~SparseMatrix()
	{
		for (int i = 0; i < M; i++)
		{
			Node* temp = Row_List[i];
			if (temp->Next_in_Row == NULL)
			{

			}
			else if (temp->Next_in_Row->Next_in_Row == NULL)
			{
				temp = temp->Next_in_Row;
				delete temp;
			}
			else
			{
				while (temp->Next_in_Row->Next_in_Row != NULL)
				{
					temp = temp->Next_in_Row;
				}
				Node* temp2 = temp;
				temp->Next_in_Row = NULL;
				delete temp2;
			}
		}
		Row_List.clear();
	}
	SparseMatrix operator + (const SparseMatrix& obj)
	{
		if (M == obj.M && N == obj.N)
		{
			SparseMatrix Answer;
			Answer.M = M;
			Answer.N = N;
			//Making the row List
			for (int i = 1; i <= M; i++)
			{
				Node* temp = new Node(i);
				temp->Next_in_Row = NULL;
				temp->col_index = 0;
				Answer.Row_List.push_back(temp);
			}
			for (int i = 0; i < M; i++)
			{
				int k;
				int l;
				Node* ij1 = Row_List[i];
				Node* ij2 = obj.Row_List[i];
				ij1 = ij1->Next_in_Row;
				ij2 = ij2->Next_in_Row;
				if (ij1 == NULL || ij2 == NULL)
				{
					if (ij1 == NULL && ij2 == NULL)
					{
						Answer.Row_List[i]->Next_in_Row = NULL;
						continue;
					}


				}
				k = 0;
				l = 0;
				if(ij1!=NULL)
				 k = ij1->col_index;
				if(ij2!=NULL)
				 l = ij2->col_index;

				bool check1 = false;
				bool check2 = false;
				for (int j = 1; j <= N && (ij1!=NULL || ij2!=NULL); j++)
				{

					if (j == k || j == l)
					{
					 if (j == k && j == l)
					{
						Node* n1 = new Node;
						n1->col_index = j;
						n1->value = ij2->value + ij1->value;
						add(Answer.Row_List[i], n1);
						check1 = true;
						check2 = true;

					}
					 else if (j == k && j!= l)
						{
							Node* n1 = new Node;
							n1->col_index = j;
							n1->value = ij1->value;
							add(Answer.Row_List[i], n1);
							check1 = true;

						}

					 else if (j != k && j == l)
						{
							Node* n1 = new Node;
							n1->col_index = j;
							n1->value = ij2->value;
							add(Answer.Row_List[i], n1);
							check2 = true;
						}
					 if (ij1 != NULL && check1)
					 {
						 ij1 = ij1->Next_in_Row;
						 check1 = false;
					 }
					 if (ij2 != NULL && check2)
					 {
						 ij2 = ij2->Next_in_Row;
						 check2 = false;
					 }
						if (ij1 == NULL)
						{
							k = -1;
						}
						else
						{
							k = ij1->col_index;

						}
						if (ij2 == NULL)
						{
							l = -1;
						}
						else
						{
							l = ij2->col_index;

						}
				    }
				}
				
			}
			return Answer;

		}
		else
		{
			cout << "ADDITION IS NOT POSSIBLE ";
			return *this;
		}
	}
	SparseMatrix operator * (const SparseMatrix& obj)
	{
		if (N != obj.M)
		{
			cout << "MUlTIPLICATION IS NOT POSSIBLE";
			return *this;
		}
		else {
			SparseMatrix Answer;
			Answer.M = M;
			Answer.N = obj.N;
			int sum = 0;
			//Making the row List
			for (int i = 1; i <= M; i++)
			{
				Node* temp = new Node(i);
				temp->Next_in_Row = NULL;
				temp->col_index = 0;
				Answer.Row_List.push_back(temp);
			}
			SparseMatrix C;
			C = obj;
			C = C.Transpose();

			for (int i = 0; i < Answer.M; i++)
			{
				Node* temp = Row_List[i]->Next_in_Row;
				int row_List = 0;
				for (int j = 1; j <= Answer.N; j++)
				{
					int sum = 0;
					Node* temp2 = C.Row_List[row_List]->Next_in_Row;
					temp = Row_List[i]->Next_in_Row;
					while (temp != NULL && temp2!=NULL)
					{					
						if (temp->col_index == temp2->col_index)
						{
							sum = sum + (temp->value * temp2->value);
						}
						if (temp->col_index > temp2->col_index)
						{
							temp2 = temp2->Next_in_Row;
						}
						else
						{
							temp = temp->Next_in_Row;
						}
					}
					if (sum != 0)
					{
						Node* nn = new Node;
						nn->value = sum;
						nn->col_index = j;
						add(Answer.Row_List[i], nn);
					}

					row_List++;
				}
			}
		    
			return Answer;
		}
		

	}
	SparseMatrix Transpose ()
	{
		SparseMatrix Answer;
		Answer.M = N;
		Answer.N = M;
		//Making the row List
		for (int i = 1; i <= Answer.M; i++)
		{
			Node* temp = new Node(i);
			temp->Next_in_Row = NULL;
			temp->col_index = 0;
			Answer.Row_List.push_back(temp);
		}
		int row_counter = 0;
		int* col_numbers = new  int[Answer.M];
		for (int i = 0; i <Answer.M; i++)
		{
			col_numbers[i] = 1;
		}

		Node* temp = Row_List[row_counter]->Next_in_Row;
		bool check = true;
		while (row_counter<M)
		{
			
			if (temp == NULL)
			{
				row_counter++;
				if (row_counter == M)
				{
					break;
				}
				temp = Row_List[row_counter]->Next_in_Row;
		         
				for (int i = 0; i < Answer.M; i++)
				{
					col_numbers[i]=col_numbers[i]+1;
					
				}

				continue;
			}
			else
			{
				Node* temp2 = new Node;
				temp2->value = temp->value;
				temp2->col_index = col_numbers[temp->col_index];
				add(Answer.Row_List[temp->col_index - 1], temp2);
				temp = temp->Next_in_Row;				
			}

			
		}
		int d = Answer.M - Answer.N;
		int checker = 0;
		if (d < 0)
		{
			d = -(d);
		}
		if (Answer.N > Answer.M)
		{
			 checker = -(d);
		}
		else
		{
			checker = d;
		}
		row_counter = 0;
		int col = 1;
		Node* temp3 = Answer.Row_List[Answer.M - 1];
		Node* temp4= Row_List[row_counter]->Next_in_Row;
		temp3->Next_in_Row = NULL;
		while (row_counter<M)
		{

			if (temp4 == NULL)
			{
				col++;
				row_counter++;
				if (row_counter == M)
				{
					break;
				}
			    temp4 = Row_List[row_counter]->Next_in_Row;
			}
			else if (temp4->col_index == Answer.N+checker)
			{
				Node* temp5 = new Node;
				temp5->value = temp4->value;
				temp5->col_index = col;
				add(temp3, temp5);
				col++;
				row_counter++;
				if (row_counter == M)
				{
					break;
				}
				temp4 = Row_List[row_counter]->Next_in_Row;		
			}
			else
			{
				temp4=temp4->Next_in_Row;
			}

		}

		

		return Answer;
	}
	bool operator==(const SparseMatrix& obj)
	{
		if (M != obj.M || N != obj.N)
		{
			return false;
		}
		else
		{
			bool check = true;
			for (int i = 0; i < M; i++)
			{
				Node* temp = Row_List[i]->Next_in_Row;
				Node* temp2 = obj.Row_List[i]->Next_in_Row;
				  while(temp!=NULL && temp2!=NULL)
				{
					if (temp->value == temp2->value && temp->col_index == temp2->col_index)
					{
						temp = temp->Next_in_Row;
						temp2 = temp2->Next_in_Row;
						if (temp2 == NULL && temp!=NULL)
						{
							return false;
						}
						if (temp == NULL && temp2 != NULL)
						{
							return false;
						}
					}
					else
					{
						return false;
					}

				}
			}
		}
		return true;
	}
	void symmetric_and_skew_symmetric()
	{
		SparseMatrix B;
		B = this->Transpose();
		if (B == *this)
		{
			cout << endl;
			cout << "It is Symmetric";
			cout << endl;
		}
		else
		{
			cout << endl;
			cout << "It is not  Symmetric";
			cout << endl;

		}
		SparseMatrix C;
		C = *this;
		for (int i = 0; i < C.M; i++)
		{
			Node* temp = C.Row_List[i]->Next_in_Row;
			while (temp != NULL)
			{
				temp->value = -(temp->value);
				temp = temp->Next_in_Row;
			}
		}
		if (B == C)
		{
			cout << endl;
			cout << "It is Skew Symmetric";
			cout << endl;
		}
		else
		{
			cout << endl;
			cout << "It is not Skew Symmetric";
			cout << endl;
		}
	}
	bool subMatrix(const SparseMatrix& obj)
	{
		if (M < obj.M || N < obj.N)
		{
			return false;
		}
		else
		{
			Node* temp2= obj.Row_List[0]->Next_in_Row;
			bool check = true;
			bool check4 = true;
			bool check5 = true;
			bool *check2 =new bool[obj.M];
			int *col_equal_check= new int[obj.M];
			for (int i = 0; i < obj.M; i++)
				check2[i] = false;
			for (int i = 0; i < obj.M; i++)
				col_equal_check[i] = 0;

			temp2 = obj.Row_List[0]->Next_in_Row;
			for (int i = 0,k=0; i < M && k<obj.M; i++)
			{

				Node* temp = Row_List[i]->Next_in_Row;

				if (check)
				{
					temp2 = obj.Row_List[k]->Next_in_Row;
					k++;
					
				}
			/*	if (check == false)
				{
					temp2 = obj.Row_List[k]->Next_in_Row;

				}
				if (check == false)
				{
					col_equal_check[k] = 0;
				}*/
				if (temp2 == NULL || temp == NULL)
				{
					continue;

				}
				if (temp2 == obj.Row_List[(obj.M) - 1]->Next_in_Row)
				{
					check4 = false;
				}
				while (temp != NULL && temp2 != NULL)
				{
					if (temp->value == temp2->value)
					{
						temp = temp->Next_in_Row;
						temp2 = temp2->Next_in_Row;
						check = true;
						col_equal_check[k-1]++;
					}
					else
					{
						temp = temp->Next_in_Row;
						check = false;
					}

					if (temp == NULL && temp2!=NULL)
					{
						check = false;
						check5 = true;
					}
					if (check4 == false)
					{
						if (temp2 == NULL)
							break;
						else
						{
							check4 = true;
							check = false;
							check5 = false;
						}
					}

				}

				if (check4 == false)
				{
						break;
				}
			}

			for (int i = 0; i < obj.M; i++)
			{
				Node* temp =obj.Row_List[i]->Next_in_Row;
				int count = 0;
				while (temp != NULL)
				{
					count++;
					temp = temp->Next_in_Row;
				}
				cout << col_equal_check[i] << " ";
				if (count == col_equal_check[i])
				{
					check2[i] = true;
				}

			}
			for (int i = 0; i < obj.M; i++)
			{
				if (check2[i])
				{
				}
				else
				{
					return false;
				}
			}
			return true;

		}

	}
	int determinant()
	{
		int d1 = 0;
		int d2 = 0;
		int d3 = 0;
		Node* temp = Row_List[0]->Next_in_Row;
		Node* temp2 = Row_List[1]->Next_in_Row;
		if (temp == NULL || temp2 == NULL)
		{
			d3 = 0;
		}
		else
		{
			if (temp2->col_index == 1)
				temp2 = temp2->Next_in_Row;
			if (temp2 != NULL)
			{
				if (temp->col_index == 1 && temp2->col_index == 2)
				{
					d1 = temp->value * temp2->value;
				}
			}
			if (temp->col_index == 1)
				temp = temp->Next_in_Row;

			temp2 = Row_List[1]->Next_in_Row;
			if (temp != NULL)
			{
				if (temp->col_index == 2 && temp2->col_index == 1)
				{
					d2 = temp->value * temp2->value;
				}
			}
			d3 = d1 - d2;
		}
		return d3;
	}
	SparseMatrix inverse()
	{
		if (M != N)
		{
			cout << "INVERSE IS NOT POSSIBLE";
			return *this;
		}
		if (M > 2 || N > 2)
		{
			cout << "ONLY FOR 2x2 MATRIX";
			return *this;
		}
		else
		{
			Node* temp = Row_List[0]->Next_in_Row;
			Node* temp2 = Row_List[1]->Next_in_Row;
			int* temp3 = new int[4];
			for (int i = 0; i < 4; i++)
			{
				temp3[i] = 0;
			}

		
				if (temp != NULL)
				{
					temp3[temp->col_index - 1] = temp->value;
					temp = temp->Next_in_Row;
					if (temp != NULL)
					{
						temp3[temp->col_index - 1] = temp->value;
					}
				}

				if (temp2 != NULL)
				{
					temp3[temp2->col_index + 1] = temp2->value;
					temp2 = temp2->Next_in_Row;
					if (temp2 != NULL)
					{
						temp3[temp2->col_index + 1] = temp2->value;
					}
				}
				int k = temp3[0];
				temp3[0] = temp3[3];
				temp3[3] = k;
				temp3[2] = -(temp3[2]);
				temp3[1] = -(temp3[1]);

				SparseMatrix obj;
				obj.M = M;
				obj.N = N;

				for (int i = 1; i <= obj.M; i++)
				{
					Node* temp = new Node(i);
					temp->Next_in_Row = NULL;
					temp->col_index = 0;
					obj.Row_List.push_back(temp);
				}


			int d = this->determinant();
			if (d == 0)
			{
				cout << "Inverse not possible";
				return *this;
			}
			for (int i = 0; i < 2; i++)
			{
				if (temp3[i] != 0)
				{
					Node* nn = new Node();
					nn->col_index = i + 1;
					nn->value = temp3[i]/d;
					add(obj.Row_List[0], nn);
				}
			}
			for (int i = 0,k=2; i < 2; i++,k++)
			{
				if (temp3[k] != 0)
				{
					Node* nn = new Node();
					nn->col_index = i + 1;
					nn->value = temp3[k]/d;
					add(obj.Row_List[1], nn);
				}
			}
			return obj;
		}
	}
	void print_TA()
	{
		Node* current = NULL;
		for (int i = 0; i < M; i++)
		{
			current = Row_List[i]->Next_in_Row;
			cout << "Row[" << i+1 << "]" << " => ";
			while (current->Next_in_Row != 0)
			{
				cout << "[ " << current->col_index << " , " << current->value << " ]" << " => ";
				current = current->Next_in_Row;
			}
			cout << "[ " << current->col_index << " , " << current->value << " ]";
			cout << endl;
		}



	}
	bool subMatrix_2(const SparseMatrix& obj)
	{
		if (M < obj.M || N < obj.N)
		{
			return false;
		}
		else
		{
			bool* checks = new bool[obj.M];
			int* col_equal_check = new int[obj.M];
			int* col_index_check = new int[obj.M];
			for (int i = 0; i < obj.M; i++)
				checks[i] = false;
			for (int i = 0; i < obj.M; i++)
				col_equal_check[i] = 0;
			for (int i = 0; i < obj.M; i++)
				col_index_check[i] = 0;
			for (int i = 0, k = 0; i < M && k < obj.M; i++)
			{
				Node* temp = Row_List[i]->Next_in_Row;
				Node* temp2 = obj.Row_List[k]->Next_in_Row;
				if (temp2 == NULL)
				{
					k++;
					continue;
				}
				if (temp == NULL)
				{
					continue;
				}
				while (temp != NULL || temp2 != NULL)
				{
					if (temp == NULL || temp2==NULL)
					{
						break;
					}
					if (temp->value == temp2->value)
					{
						col_equal_check[k]++;
						col_index_check[k] = col_index_check[k] - temp->col_index;
						temp2 = temp2->Next_in_Row;
					}
					else
					{
						temp = temp->Next_in_Row;
					}
				}
				if (temp2 == NULL)
				{
					k++;
				}
				else
				{
					col_equal_check[k] = 0;
					col_index_check[k] = 0;
				}
			}
			int elements = 0;
			for (int i = 0; i < obj.M; i++)
			{
				Node* temp = obj.Row_List[i]->Next_in_Row;
				int count = 0;
				while (temp != NULL)
				{
					count++;
					temp = temp->Next_in_Row;
				}
				elements = elements + count;
				if (count == col_equal_check[i])
				{
					checks[i] = true;
				}

			}
			int f = col_index_check[0];
			if (elements == obj.M * obj.N)
			{
				for (int i = 0; i < obj.M; i++)
				{
					if (col_index_check[i] != f)
					{
						checks[i] = false;
					}
				}
			}

			for (int i = 0; i < obj.M; i++)
			{
				if (checks[i])
				{
				}
				else
				{
					return false;
				}
			}
			return true;



		}

	}

};
int main()
{
	/*Read Constructor test */
	SparseMatrix ob("OBJ.txt");
	ob.print();
	ob.print_TA();
	cout << endl;
	//Copy Constructor test
	SparseMatrix ob2("OBJ2.txt");
	ob2.print();
	cout << endl;
	//Assignment operator test and addition test
	cout << "ADDITION" << endl;
	SparseMatrix ob3;
	ob3=ob2+ob;
	ob3.print();
	cout << endl;

	//Transpose test
	SparseMatrix ob4;
	cout << "Transpse:" << endl;
	ob4 = ob.Transpose();
	ob4.print();
	cout << endl;


	//Multiplication test
	cout << "MULTIPLICATION" << endl;
	SparseMatrix ob5;
	ob5 = ob * ob2;
	ob5.print();


	//== Operator
	if (ob == ob2)
		cout << "Yes";
	else
		cout << "NO";

	cout << endl << endl;
	//Skew and Symmetric test
	ob.symmetric_and_skew_symmetric();

	cout << endl << endl;
	//Sub Matrix Test
	if(ob.subMatrix_2(ob2))
	cout<<"Its is a Sub Matrix";
	else
	cout << "Its is not a Sub Matrix";
	cout << endl << endl;
	ob=ob2.inverse();
	ob.print();
	


	return 0;
}