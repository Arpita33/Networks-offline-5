#include <bits/stdc++.h>
using namespace std;

void print_vector(vector<string> vect)
{
	int size=vect.size();
	
	for(int i=0;i<size;i++)
	{
		string str=vect[i];
		int weee=0;
		for(int j=0;j<str.size();j++)
		{
			if(j==(pow(2,weee)-1))
			{
				printf("\033[38;2;50;205;50m%c\033[0m",str[j]);
				weee++;
			}
			else
			{
				printf("%c",str[j]);
			}
		}
		printf("\n");
	}
}




string padString(string str, int m)
{
	int size=str.size();
	//cout<<"size of data string= "<<size<<endl;

	int remainder=size%m;
	if(remainder!=0)
	{
		//cout<<"Size of data string not a multiple of m.\n";
		for(int i=0;i<(m-remainder);i++)
		{
			str+="~";
		}
		//cout<<str<<endl;	
	}
	return str;

}

string makeDataBlock(string str, int m)
{

	string ret_str="";
	for(int j=0;j<str.size();j++)
	{
		//printf("Ascii of %c = %d\n",str[j],str[j] );
		for(int i=0;i<8;i++)
		{
			int bit=(str[j]>>(7-i)&1);
			//printf("%d",bit);
			char b=bit+'0';
			ret_str+=b;
		}
		if((j+1)%m==0)
		{
			ret_str+="\n";
		}
		//printf("\n");
	}
	//printf("%s\n", ret_str.c_str());
	return ret_str;
}


vector<string> string_split(string s)
{
	string str=s;
	vector<string> tokens;
	string delimiter = "\n";

	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos) {
	    token = str.substr(0, pos);
	    tokens.push_back(token);
	    //cout << token << endl;
	    str.erase(0, pos + delimiter.length());
	}
	return tokens;
	
}





int calculte_no_of_checkbits(int m)
{
	int bits_in_a_row=m*8;
	int count=0;
	int r=0;
	while(count<bits_in_a_row)
	{
		
		count+=pow(2,r)-1;
		r++;

	}
	//printf("Number of data bits %d\n", bits_in_a_row);
	//printf("Number of check bits= %d\n",r);
	return r;

}

vector<string> insert_check_bits(string s, int m)
{
	vector<string> row_vect=string_split(s);
	vector<string> new_vect,temp_vect;
	int r=calculte_no_of_checkbits(m);
	for(int k=0;k<row_vect.size();k++)
	{
		string str=row_vect[k];		
		string modified_str="";
		int new_length=str.size()+r;
		int w=0;
		int w1=0;
		for(int i=0;i<new_length;i++)
		{
			if(i==(pow(2,w)-1))
			{
				modified_str+='0';
				w++;
			}
			else
			{
				modified_str+=str[w1++];

			}

		}
		


		for(int i=0;i<r;i++)
		{
			int no_of_1s=0;
			int start=(int)pow(2,i);
			for(int j=start+1;j<=new_length;j++)
			{
				//printf("Position: %d\n", j);
				if((j & start) != 0 )
				{
					//printf("Check bit: %d, position= %d, value= %d \n", start,j,modified_str[j]-'0');
					if(modified_str[j-1]-'0'==1)
					{
						no_of_1s++;
					}
				}
			}
			if((no_of_1s%2)==0)
			{
				//printf("Even parity\n");

				modified_str[start-1]='0';
			}
			else
			{
				//printf("Odd parity\n");
				modified_str[start-1]='1';
			}
		}

		//cout<<modified_str<<endl;
		new_vect.push_back(modified_str);

	}


	return new_vect;
}

string column_wise_serialization(vector<string> vect)
{
	string str="";
	int rows=vect.size();
	int columns=vect[0].size();
	for(int i=0;i<columns;i++)
	{
		for(int j=0;j<rows;j++)
		{
			//printf("%c", vect[j][i]);
			str+=vect[j][i];
		}
	}
	return str;
}




int BitStringToInt(string str)
{
	int b=0;
	unsigned int ret_integer=0;
	for(int i=str.size()-1;i>=0;i--)
	{
		ret_integer+=(unsigned int)(str[i]-'0')*pow(2,b);
		b++;
	}
	//printf("Equivalent integer: %d\n", ret_integer);
	return ret_integer;
}



string CRC(string generator_polynomial, string str)
{
	string quotient="";
	int degree=generator_polynomial.size()-1;
	string frame=str;
	for(int i=0;i<degree;i++)
	{
		frame+='0';
	}
	//cout<<"Before division: Dividend= "<<frame<<endl;
	int steps=0;
	string remainder="";
	int last_used_index;
	string frame_extract=frame.substr(0,degree+1);
	last_used_index=degree;
	int substract_flag_on=0;
	while(last_used_index<frame.size())
	{

		steps++;
		frame_extract[degree]=frame[last_used_index++];
		//cout<<"\nAfter "<<steps<<" steps:\n";
		//cout<<"Before shifting frame_extract= "<<frame_extract<<endl;
		if(frame_extract[0]=='0')
		{

			quotient+='0';
			
			substract_flag_on=0;
		}
		else
		{
			quotient+='1';
			//frame_extract[degree]=frame[++last_used_index];				
			substract_flag_on=1;
			//break;
		}
		
		
		
		//cout<<"quotient= "<<quotient<<endl;
		//cout<<"frame_extract= "<<frame_extract<<endl;

		if(substract_flag_on)
		{
				remainder="";
				for(int i=0;i<degree+1;i++)
				{
					unsigned int a=frame_extract[i]-'0';
					unsigned int b=generator_polynomial[i]-'0';
					if((a^b)==1)
					{
						remainder+='1';
					}
					else
					{
						remainder+='0';
					}

				}
				for(int i=0;i<degree;i++)
				{
					frame_extract[i]=remainder[i+1];
				}
				frame_extract[degree]='0';
			//cout<<"remainder copied to frame_extract = "<<frame_extract<<endl;
		}
		else
		{
				for(int i=0;i<degree+1;i++)
				{
					remainder[i]=frame_extract[i];
				}
				for(int i=0;i<degree;i++)
				{
					frame_extract[i]=frame_extract[i+1];
				}
				frame_extract[degree]='0';


		}

		//cout<<"remainder= "<<remainder<<endl;




	}
	//cout<<"quotient= "<<quotient<<endl;
	//cout<<"remainder= "<<remainder<<endl;
	cout<<"\nDatabits after appending CRC checksum (sent frame):"<<endl;
	cout<<str;

	string str_with_checksum=str;
	for(int i=1;i<=degree;i++)
	{
		str_with_checksum+=remainder[i];
		printf("\033[38;2;0;255;255m%c\033[0m",remainder[i]);

	}
	cout<<endl;
	//cout<<str_with_checksum<<endl;*/
	return str_with_checksum;

}

float random_probability()
{
	double max = RAND_MAX;
	float num = rand()/max;
	return num;
}

string toggle2(string str, float probability)
{
	string erroneous_string = str;
	int databits = str.size();
	
	for(int i = 0; i < str.size(); i++)
	{
		float rand2 = random_probability();
		if(probability > rand2)
		{
			if(erroneous_string[i]=='0')
			{
				erroneous_string[i]='N';
			}
			else
			{
				erroneous_string[i]='Z';
			}
		}
	}
	cout<<"Received Frame: "<<endl;
	//cout<<erroneous_string<<endl;

	for(int i=0;i<databits;i++)
	{
		if(erroneous_string[i]=='N')
		{
			//erroneous_string[i]='1';
			printf("\033[38;2;255;0;0m%c\033[0m",'1');

		}
		else if(erroneous_string[i]=='Z')
		{
			//erroneous_string[i]='0';
			printf("\033[38;2;255;0;0m%c\033[0m",'0');
		}
		else
		{
			cout<<erroneous_string[i];
		}
	}
	cout<<endl;
	return erroneous_string;

}

string toggle(string str, float probability)
{
	string erroneous_string=str;
	int databits=str.size();
	cout<<endl;
	//cout<<"databits= "<<databits<<endl;

	int erroneous_bits=probability*databits;
	//cout<<"erroneous_bits= "<<erroneous_bits<<endl;
	int bit_gap=0;
	if(erroneous_bits!=0)
	{
		bit_gap=databits/erroneous_bits;

		//cout<<"bit gap= "<<bit_gap<<endl;
		for(int i=0;i<databits;)
		{
			i+=bit_gap;
			if(erroneous_string[i]=='0')
			{
				erroneous_string[i]='N';
			}
			else
			{
				erroneous_string[i]='Z';
			}
			

		}
	}
	cout<<"Received Frame: "<<endl;
	//cout<<erroneous_string<<endl;

	for(int i=0;i<databits;i++)
	{
		if(erroneous_string[i]=='N')
		{
			//erroneous_string[i]='1';
			printf("\033[38;2;255;0;0m%c\033[0m",'1');

		}
		else if(erroneous_string[i]=='Z')
		{
			//erroneous_string[i]='0';
			printf("\033[38;2;255;0;0m%c\033[0m",'0');
		}
		else
		{
			cout<<erroneous_string[i];
		}
	}
	cout<<endl;
	return erroneous_string;

}

void Error_Detection(string generator_polynomial, string received_str)
{
	int databits=received_str.size();
	string frame="";
	for(int i=0;i<databits;i++)
	{
		if(received_str[i]=='N')
		{
			frame+='1';
			
		}
		else if(received_str[i]=='Z')
		{
			frame+='0';
		}
		else
		{
			frame+=received_str[i];
		}
	}


	string quotient="";
	int degree=generator_polynomial.size()-1;
	
	int steps=0;
	string remainder="";
	int last_used_index;
	string frame_extract=frame.substr(0,degree+1);
	last_used_index=degree;
	int substract_flag_on=0;
	while(last_used_index<frame.size())
	{

		steps++;
		frame_extract[degree]=frame[last_used_index++];

		if(frame_extract[0]=='0')
		{

			quotient+='0';
			
			substract_flag_on=0;
		}
		else
		{
			quotient+='1';				
			substract_flag_on=1;

		}
		//cout<<"\n\nAt error detection, frame_extract= "<<frame_extract<<endl;

		if(substract_flag_on)
		{
				remainder="";
				for(int i=0;i<degree+1;i++)
				{
					unsigned int a=frame_extract[i]-'0';
					unsigned int b=generator_polynomial[i]-'0';
					if((a^b)==1)
					{
						remainder+='1';
					}
					else
					{
						remainder+='0';
					}

				}
				for(int i=0;i<degree;i++)
				{
					frame_extract[i]=remainder[i+1];
				}
				frame_extract[degree]='0';

		}
		else
		{
				for(int i=0;i<degree+1;i++)
				{
					remainder[i]=frame_extract[i];
				}
				for(int i=0;i<degree;i++)
				{
					frame_extract[i]=frame_extract[i+1];
				}
				frame_extract[degree]='0';


		}
		//cout<<"At error detection, remainder= "<<remainder<<endl;
	}

		bool flag=true;
		for(int i=0;i<remainder.size();i++)
		{
			if(remainder[i]=='1')
			{
				flag=false;
				break;
			}
		}

		cout<<"\nResult of CRC checksum matching: ";

		if(!flag)
		{
			cout<<"ERROR DETECTED"<<endl;

		}
		else
		{
			cout<<"NO ERROR DETECTED"<<endl;
		}

}

vector<string> deserialization(string str, int m, string gp)
{
	string received_frame="";
	int checksum_size=gp.size()-1;
	int new_size=str.size()-checksum_size;
	for(int i=0;i<new_size;i++)
	{
		received_frame+=str[i];
	}
	int count=0;
	int r=calculte_no_of_checkbits(m);
	int no_of_cols=m*8+r;
	int no_of_rows=new_size/no_of_cols;
	vector<string> vect_block(no_of_rows);
	for(int i=0;i<no_of_cols;i++)
	{
		for(int j=0;j<no_of_rows;j++)
		{
			vect_block[j]+=received_frame[count++];
		}
	}

	cout<<"\nData block after removing CRC checksum bits: "<<endl;

	for(int i=0;i<no_of_rows;i++)
	{
		for(int j=0;j<no_of_cols;j++)
		{
			if(vect_block[i][j]=='N')
			{
				printf("\033[38;2;255;0;0m%c\033[0m",'1');
				vect_block[i][j]='1';
			}
			else if(vect_block[i][j]=='Z')
			{
				printf("\033[38;2;255;0;0m%c\033[0m",'0');
				vect_block[i][j]='0';
			}
			else
			{
				cout<<vect_block[i][j];
			}
		}
		cout<<endl;

	}

	return vect_block;

}
vector<string> remove_checkBits(vector<string> corrected_vect);
vector<string> errorCorrection(int m, vector<string> block)
{
	int r=calculte_no_of_checkbits(m);
	
	for(int k=0;k<block.size();k++)
	{
		int count=0;
		
		for(int i=0;i<r;i++)
		{
			int no_of_1s=0;
			int start=(int)pow(2,i);
			for(int j=start;j<=block[k].size();j++)
			{
				//printf("Position: %d\n", j);
				if((j & start) != 0 )
				{
					if(block[k][j-1]-'0'==1)
					{
						no_of_1s++;
					}
				}
			}
			if((no_of_1s%2)!=0)
			{
				//odd parity!!!
				count+=start;
				
			}

		}


		if(count>0 && count < block[0].size())
		{
			//cout<<"For row "<<k<<" Error at bit position: "<<count-1<<endl;
			if(block[k][count-1]=='1')
			{
				block[k][count-1]='0';
			}
			else
			{
				block[k][count-1]='1';
			}
		}
	}


	vector<string> ret_vect=remove_checkBits(block);
	cout<<"\nData block after removing checkbits"<<endl;
	for(int i=0;i<ret_vect.size();i++)
	{
		cout<<ret_vect[i]<<endl;
	}

	return ret_vect;


}


vector<string> remove_checkBits(vector<string> corrected_vect)
{
	vector<string> ret_vect;
	for(int i=0;i<corrected_vect.size();i++)
	{
		int k=0;
		string s="";
		for(int j=0;j<corrected_vect[i].size();j++)
		{
			if((j+1)==pow(2,k))
			{
				k++;

			}
			else
			{
				s+=corrected_vect[i][j];
			}

		}
		ret_vect.push_back(s);
	}
	return ret_vect;
}

void form_words(int m, vector<string> block)
{
	cout<<"\nOutput frame"<<endl;
	for(int i=0;i<block.size();i++)
	{
		int start=0;
		for(int j=0;j<m;j++)
		{
			string character =block[i].substr(start,8);
			start+=8;
			int c=BitStringToInt(character);
			printf("%c", c);
		}
	}
	printf("\n");
}





int main()
{
	int m;
	float p;
	string str,gOfx;
	cout<<"Enter a string: ";
	getline(cin,str);
	//cout<<"str= "<<str<<endl;
	cout<<"Enter the number of bytes in a row (m): ";
	cin>>m;
	//cout<<"m= "<<m<<endl;
	p=0;
	while(1)
	{
		cout<<"Enter probability (p): ";
		cin>>p;
		if(p>1 || p<0)
			continue;
		else
			break;

	}

	//cout<<"p= "<<p<<endl
	
	while(true)
	{
		cout<<"Enter generator polynomial: ";
		cin>>gOfx;
		if(gOfx[0]=='0' || gOfx[gOfx.size()-1]=='0')
		{
			cout<<"Generator Polynomial must start and end with 1.\n";
			continue;
		}
		else
			break;
	}
	
	str=padString(str,m);
	cout<<"\nData String after padding: "<<str<<endl;
	string ret_string=makeDataBlock(str,m);
	cout<<"\nData block <ASCII of m characters per row>:"<<endl;
	cout<<ret_string;
	vector<string> vect_with_check_bits=insert_check_bits(ret_string,m);
	cout<<"\nData block after adding checkbits:"<<endl;
	print_vector(vect_with_check_bits);
	

	string cws=column_wise_serialization(vect_with_check_bits);
	printf("\nData bits after column wise serialization:\n");
	cout<<cws<<endl;
	//CRC
	string str_with_chksum=CRC(gOfx,cws);
	string received_frame=toggle2(str_with_chksum,p);

	Error_Detection(gOfx,received_frame);
	//Error_Detection("10011","1101011011");
	vector<string> deserialised_vect= deserialization(received_frame,m,gOfx);
	vector<string> corrected_str=errorCorrection(m, deserialised_vect);
	form_words(m,corrected_str);



}