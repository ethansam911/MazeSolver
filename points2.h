/**
    Name: Ethan Sam 
	Date: 2/14/2019
	Professor: Ioannis Stamos
	Class: CSCI 335
	
	Header file: points2.h
	
	This class constructs a series of coordinates based on user input 
	A sequence of values will determine the coordinates along with size
	For Example: 2 3 4 6 4 yields two coordinates of of size "2" : (3, 4) (6, 4)  
	
 Few comments describing the class Points2
**/
#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
// Place comments that provide a brief explanation of the class,
// and its sample usage. 
	template<typename Object>
	class Points2 {
		public:
			// Default "big five" -- you have to alter them for your assignment.
			// That means that you will remove the "= default" statement.
			//  and you will provide an implementation.

			// Zero-parameter constructor. 
			// Set size to 0.

			Points2()
			{
				size_ = 0;
				sequence_ = nullptr;
			}

			// Copy-constructor.
			Points2(const Points2 &rhs)
			{
				if(rhs.size_ == 0)
				{
				sequence_ = nullptr;
				size_ = 0;
				}
			size_ = rhs.size();
			sequence_ = new std::array<Object, 2>[rhs.size_];
			for(size_t i = 0; i < rhs.size_; ++i)
			{
				sequence_[i] = rhs.sequence_[i];
			}
			}


			// Copy-assignment. If you have already written
			// the copy-constructor and the move-constructor
			// you can just use:
			// {
			// Points2 copy = rhs; 
			// std::swap(*this, copy);
			// return *this;
			// }
			
			Points2& operator=(const Points2 &rhs)
			{
				Points2 copy = rhs; 
				std::swap(*this, copy);
				return *this; 
			}// END operator "="

			// Move-constructor.
			//rhs.sequence is a synonym of sequence_ (unupdated)
			//(100, 101) (2, 3) (40, 50) (11, 33) wasn't printed because std::swap was used 
			Points2(Points2 &&rhs):sequence_(std::move(rhs.sequence_)), size_(std::move(rhs.size_))
			{
				rhs.sequence_ =nullptr;
				rhs.size_ = 0;
			}// END Move constructor
		  

			// Move-assignment.
			// Just use std::swap() for all variables.  
			Points2& operator=(Points2 &&rhs)
			{	
				if(this != &rhs)
				{
					std::swap(sequence_, rhs.sequence_);		
					std::swap(size_, rhs.size_);
				}
			return *this;
			}// END Move-assignment
  
			//Destructor
			~Points2()
			{
				if(sequence_ != nullptr)
				{
					delete[] sequence_;
				}
			sequence_ = nullptr;
			}//END destructor

			// End of big-five.
			// One parameter constructor._
			//This one array holds two objects
			//An object can be either a double or integer
			// item and squence are both of type array (both hold two objects)
  
			Points2(const std::array<Object, 2>& item) 
			{
	 
				sequence_ = new std::array<Object, 2>[1]; 
				sequence_[0] = item;
				size_ = 1;  
			}


			// Overloading the << operator
			//This is a string remember
			friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) 
			{
				if(some_points2.size_==0)
				{
					out << "(" << ")";
				}
				else if(some_points2.size_>=1)
				{
					for(size_t i = 0; i < some_points2.size_ ; ++i)
					{		
						out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
					}
				}
			return out;
			}

			// Read a chain from standard input.
			//"This" refers to the class members
			//Possible error conditions for this function were from an incorrect assignment of  
			//  
			void ReadPoints2() 
			{
	 
				// Part of code included (without error checking).
				std::string input_line;
				std::getline(std::cin, input_line); 
				std::stringstream input_stream(input_line);
				if (input_line.empty()) return;
	
				// Read size of sequence (an integer).
				int size_of_sequence;
				input_stream >> size_of_sequence;
				
				// Allocate space for sequence.
				// Add code here.
				//We allocate size_ and sequence_ pointer to be in this specific class instance
				size_ = size_of_sequence;
				sequence_ = new std::array<Object, 2>[size_of_sequence];
	
				// Read coordinates
				// Fill sequence_ here.
				Object token;
				for (int i = 0 ;input_stream >> token; ++i) 
				{
					sequence_[i][0] = token; input_stream >> token; sequence_[i][1] = token; 
				}
			}
  

				size_t size() const 
				{
					return size_;
				}

				// @location: an index to a location in the sequence.
				// @returns the point at @location.
				// const version.
				// abort() if out-of-range.
				const std::array<Object, 2>& operator[](size_t location) const 
				{ 
					if((location >= size_)||(location < 0))
					{	  
						abort();
					}
					else
					{
						return sequence_[location];
					}
					return sequence_[location];
				} //END operator[]
  
			    //  @c1: A sequence.
				//  @c2: A second sequence.
				//  @return their sum. If the sequences are not of the same size, append the
				//    result with the remaining part of the larger sequence.
				friend Points2 operator+(const Points2 &c1, const Points2 &c2) 
				{
	 
					Points2 return_value;
					size_t smaller_size, larger_size;
	
	
					if(c1.size() > c2.size())
					{
						return_value.sequence_ = new std::array<Object, 2>[c1.size_];
						larger_size = c1.size();
						smaller_size = c2.size();
					}
					else if ( c1.size() < c2.size())
					{
						return_value.sequence_ = new std::array<Object, 2>[c2.size_];
						larger_size = c2.size();
						smaller_size = c1.size();
					}
	
					for(unsigned i = 0; i < smaller_size ; ++i)
					{
						return_value.sequence_[i][0] =  c1.sequence_[i][0] +c2.sequence_[i][0];
						return_value.sequence_[i][1] =  c1.sequence_[i][1] +c2.sequence_[i][1];
					}
					
					if(c1.size() > c2.size())
					{
						for(unsigned i = smaller_size; i < larger_size ; ++i)
						{
							return_value.sequence_[i][0] = c1.sequence_[i][0];
							return_value.sequence_[i][1] = c1.sequence_[i][1];
						}
					}
					else if(c1.size() < c2.size())
					{
						for(unsigned i = smaller_size; i < larger_size ; ++i)
						{
							return_value.sequence_[i][0] = c2.sequence_[i][0];
							return_value.sequence_[i][1] = c2.sequence_[i][1];
						}
					}
					return_value.size_ = larger_size;
		
				return return_value;
				}
 
 private:
  // Sequence of points. 
  //Fixed size array container of size 2; holds objects 
  //*sequence_ is a pointer to a memory location with an array holding two objects (int or double)
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

	};  // namespace teaching_project
}
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
