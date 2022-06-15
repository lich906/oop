#include <iostream>
#include "Vehicle\Concrete\PoliceCar.h"
#include "Person\Concrete\PoliceMan.h"
#include "Person\Concrete\Racer.h"
#include "Vehicle\Concrete\Taxi.h"
#include "Person\Concrete\Person.h"

void PrintPersonInfo(std::ostream& output, const IPerson& person)
{
	output << "Person name: " << person.GetName();
	try
	{
		const PoliceMan& policeManRef = dynamic_cast<const PoliceMan&>(person);
		output << ", Profession: Police man, Department name: " << policeManRef.GetDepartmentName() << std::endl;
	}
	catch (const std::bad_cast&)
	{
		try
		{
			const Racer& racerRef = dynamic_cast<const Racer&>(person);
			output << ", Profession: Racer, Awards count: " << racerRef.GetAwardsCount() << std::endl;
		}
		catch (const std::bad_cast&)
		{
			output << std::endl;
			return;
		}
	}
}

template<typename VehiclePtr>
void PrintVehiclePassengersInfo(std::ostream& output, const VehiclePtr& vehicle)
{
	for (size_t i = 0; i < vehicle->GetPassengerCount(); ++i)
	{
		PrintPersonInfo(output, vehicle->GetPassenger(i));
	}
}

int main()
{
	PoliceCar policeCar(5, MakeOfCar::FORD);
	PoliceMan johnSmith("John Smith", "North-Western police department");
	PoliceMan jimClark("Jim Clark", "South-Eastern police department");
	policeCar.AddPassenger(std::make_shared<PoliceMan>(johnSmith));
	policeCar.AddPassenger(std::make_shared<PoliceMan>(jimClark));
	std::cout << "I. Passengers in police car:" << std::endl;
	PrintVehiclePassengersInfo(std::cout, std::make_shared<PoliceCar>(policeCar));

	policeCar.RemovePassenger(1);
	Taxi taxi(2, MakeOfCar::TOYOTA);
	Person rajaGandhi("Raja Gandhi");
	Racer michaelSchumacher("Michael Schumacher", 91);
	taxi.AddPassenger(std::make_shared<Person>(rajaGandhi));
	taxi.AddPassenger(std::make_shared<Racer>(michaelSchumacher));
	std::cout << "II. Passengers in taxi before:" << std::endl;
	PrintVehiclePassengersInfo(std::cout, std::make_shared<Taxi>(taxi));
	taxi.RemovePassenger(0);
	taxi.AddPassenger(std::make_shared<PoliceMan>(jimClark));
	std::cout << "II. Passengers in taxi after:" << std::endl;
	PrintVehiclePassengersInfo(std::cout, std::make_shared<Taxi>(taxi));

	try
	{
		taxi.AddPassenger(std::make_shared<Person>(rajaGandhi));
	}
	catch (const std::logic_error&)
	{
		std::cout << "III. Logic exception has been catched." << std::endl;
		return 0;
	}

	return 1;
}
