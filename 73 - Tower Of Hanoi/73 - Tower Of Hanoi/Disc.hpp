#ifndef DISC_H
#define DISC_H

class Disc{
private:
	Disc();
	unsigned int m_size;

public:
	Disc(unsigned int const& size);

	//Accessors
	unsigned int size() const;

	//Operators
	bool operator<(const Disc& that) const;
	bool operator>(const Disc& that) const;
	bool operator<=(const Disc& that) const;
	bool operator>=(const Disc& that) const;
	bool operator==(const Disc& that) const;
	bool operator!=(const Disc& that) const;
};

#endif