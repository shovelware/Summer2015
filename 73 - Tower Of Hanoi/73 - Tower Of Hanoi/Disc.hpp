#ifndef DISC_H
#define DISC_H

class Disc{
private:
	Disc();
	unsigned int m_size;

public:
	Disc(unsigned int const& size);

	//Accessors
	int size() const;

	//Operators
	bool operator<(const Disc& other) const;
	bool operator>(const Disc& other) const;
	bool operator<=(const Disc& other) const;
	bool operator>=(const Disc& other) const;
	bool operator==(const Disc& other) const;
	bool operator!=(const Disc& other) const;
};

#endif