#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <sstream>

#pragma push(pack, 1)
struct MyPakcet
{
	std::string name;
	int level;
	int exp;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& name;
		ar& level;
		ar& exp;
	}


};
#pragma pack(pop)


int main()
{
	MyPakcet packet;
	packet.exp = 100;
	packet.level = 10;
	packet.name = "¿À¸®";
	
	std::stringstream ss;
	boost::archive::text_oarchive oa(ss);
	
	oa << packet;

	ss.str() = "";

	std::cout << ss.str() << std::endl;

	boost::archive::text_iarchive ia(ss);
	
	MyPakcet newPacket;
	ia >> newPacket;

	std::cout << newPacket.exp << std::endl;
	std::cout << newPacket.level << std::endl;
	std::cout << newPacket.name << std::endl;

	return(0);
}