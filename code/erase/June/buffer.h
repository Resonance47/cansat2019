#ifndef BUFFER_H_
#define BUFFER_H_

////////////////////////////////////////////////// Defines

#define BUFFER_SIZE 16 // размер буфера, количество элементов типа unsigned char


////////////////////////////////////////////////// Class "buffer"

class buffer
{
	private:
		char data[BUFFER_SIZE];
		unsigned int index;
		
		
	public:
		buffer()
		{
			index = 0;
			for (int i = 0; i < BUFFER_SIZE; i++)
				data[i] = '\0';
		}
		
		void add_one(char elem)
		{
			data[index] = elem;
			data[index + 1] = '\0';
			index++;
		}

		char *read_all()
		{
				return data;
		}

		void clear()
		{
			index = 0;
			for (int i = 0; i < BUFFER_SIZE; i++)
				data[i] = '\0';
		}
};

#endif /* BUFFER_H_ */