#ifndef HARDWARELIB_LIDAR_H_
#define HARDWARELIB_LIDAR_H_

#include <vector>

using std::vector;

namespace NRMCHardware
{
	struct ScanPoint
	{
		float dist;
		float angle;

		ScanPoint(float dist, float angle)
		{
			this->dist = dist;
			this->angle = angle;
		}
	};

	// Interface
	class Lidar : virtual public Peripheral
	{
		// Associations
		// Attributes
		// Operations
	public:
		virtual vector<ScanPoint> getScan() = 0;
		Lidar() {};
		virtual ~Lidar() {};
		virtual bool startScan() = 0;
		virtual bool stopScan() = 0;
	};
}

#endif /* HARDWARELIB_LIDAR_H_ */
