#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

// inputs -> position of cube edges (% or absolute)
//        -> edge lengths of pixels to sample (default = ?, max = img / 4)

bool compareFunc (RubixSquare a, RubixSquare b)
{
	return (a.colour < b.colour);
}

struct RubixSquare
{
	float colour;
	int face, x, y;
};

struct Vec4Uint
{
	unsigned int left, top, right, bottom;
};

class RubixFaces
{
public:
	RubixFaces(Vec4Uint offsets, unsigned int sampleSize = 0, int captureInput = 0)
		: m_offsets(offsets), 
		m_sampleSize(sampleSize),
		m_stream(captureInput)
	{
		;
	}

	// currently returns vector of squares sorted from
	// lowest colour to highest colour value
	// ie 0-9 are colour 1, 10-18 are colour 2, etc
	// TODO: better return lmao
	std::vector<RubixSquare> getSortedFaces()
	{
		std::sort(m_squares.begin(), m_squares.end(), compareFunc);

		return m_squares;
	}

	void captureFace()
	{
		if(!video.isOpened())
		{
			throw "Invalid capture stream.";
		}

		int tempSampleSize = m_sampleSize;
		cv::Mat image;
		m_stream >> image;
		cv::cvtColor(image, image, BGR2HLS);

		if(m_offsets.left + m_offsets.right > image.size().width)
		{
			throw "Error: Image exceeds horizonal bounds.";
		}
		else if(m_offsets.top + m_offsets.bottom > image.size().height)
		{
			throw "Error: Image exceeds vertical bounds.";
		}

		cv::Mat trimmed(image, 
			{m_offsets.left, m_offsets.top, m_offsets.right, m_offsets.bottom});

		// ensure sampleSize is non-zero
		if(tempSampleSize == 0)
		{
			tempSampleSize = trimmed / 30; // use 10% of each square by default
		}

		// getSamples
		for(int row = 0; row < 3; row++)
		{
			for(int column = 0; column < 3; column++)
			{
				for(int sample = 0; sample < tempSampleSize; sample++)
				{
					xCoord = trimmed.size().x / 3 * column + sample - tempSampleSize / 2;
					yCoord = trimmed.size().y / 3 * row + sample - tempSampleSize / 2;

					auto matrix = trimmed.at<double>(xCoord, yCoord);

					// TODO: finish this off: find out matrix type and store colour value
					// also possibly add in debug squares to show what is being read
					// as samples and cutoff limits on original image

					// for debugging and finding matrix type
					std::cout << "sample: " + matrix << std::endl;
				}
				// float averageColour = sum of colour samples / number of colour samples
				// m_squares.emplace_back(averageColour, m_currentFace, column, row);
			}
		}

		m_currentFace++;
	}

	void clear()
	{
		m_currentFace = 0;
		m_squares.clear();
	}

private:
	// note: sample size expects a square, hence no x/y differentiation
	int m_sampleSize, m_currentFace;
	Vec4Int m_offsets;
	cv::VideoCapture m_stream;
	std::vector<RubixSquare> m_squares;
};

// example driver program
int main()
{
	// shave 10 pixels off L/R and 20 off T/B
	// i want a 3x3 matrix of samples for each face (optional)
	// not supplying 3rd arg as zero is usually right (optional)
	RubixFaces({10, 20, 10, 20}, 3) dawgGetMeFaces; 

	// wait for slow robot
	dawgGetMeFaces.captureFace();
	// wait for slow robot some more...
	dawgGetMeFaces.captureFace();
	// rinse and repeat for each face

	// now we have 6 faces
	auto yay = dawgGetMeFaces.getSortedFaces();

	for(auto iDontHaveAVeryWellTypedReturnVectorYet : yay)
	{
		auto small = iDontHaveAVeryWellTypedReturnVectorYet;
		std::cout << small.face << ": (" small.x << ", " << small.y << ")" << endl;
	}

	// if you want to solve another cube without reinstanciating an object
	dawgGetMeFaces.clear();
	// back to square 1
	dawgGetMeFaces.captureFace();
	// etc... no need to call clear when finished with object (obviously)
	// just scope it as needed


	return(0);
}
