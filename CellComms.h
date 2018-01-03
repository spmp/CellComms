/***********************************************************
  CellComms.h - Library for reading the OSBMS Cell Monitors.
  Created by David Burkitt, March 8, 2017.
  Re-imagined by Jasper Aoranig, August, 2017.
  Released into the public domain.

  Instantiate the class with the number of cells and a
  valid Serial/Stream device.
***********************************************************/

#ifndef CellComms_h
#define CellComms_h

#include <iostream>
#include <vector>
#include <algorithm> //transform
#include <numeric>   //accumulate
#include "Arduino.h"
#include "HardwareSerial.h"
#include "Stream.h"
#include "FEC.h"

// Cell Monitors from v2.0 onwards are capable of 19200 baud
#define CELLCOMMS_BAUD			   19200

#define CTMUNENCODEDPACKETSIZE 4
#define CTMENCODEDPACKETSIZE   6

// Balancing states
#define BMS_BALANCING_NONE    0
#define BMS_BALANCING_SOME    1
#define BMS_BALANCING_ALL     3

class CellData {
  public:
  CellData(void) {};
	uint16_t millivolts     = 0;
	uint16_t temperature    = 0;
	uint8_t balancing       = 0;
	uint8_t overTemperature = 0;
	uint8_t overVoltage     = 0;
	uint8_t underVoltage    = 0;
};

class CellComms
{
  public:
  // Constructor and Initialisation
	CellComms(int numCells, Stream & port);
  void     begin(void);
  // Cell interaction
	void     sendMillivolts(int16_t millivolts);
	void     sendMillivolts(void);
	uint8_t  readCells(void);
  // Cell stats
  // Mean cell millivolts
  uint16_t millivoltsMean(void);
  // Maximum cell millivolts
  uint16_t millivoltsMax(void);
  // Minimum cell millivolts
  uint16_t millivoltsMin(void);
  // Cell number with maximum voltage
  uint8_t  millivoltsMaxCell(void);
  // Cell number with minimum voltage
  uint8_t  millivoltsMinCell(void);
  // Mean cell temperature
  uint16_t temperatureMean(void);
  // Maximum cell temperature
  uint16_t temperatureMax(void);
  // Minimum temperature
  uint16_t temperatureMin(void);
  // Cell number with maximum temperature
  uint8_t  temperatureMaxCell(void);
  // Cell number with minimum temperature
  uint8_t  temperatureMinCell(void);
  // Number of cells which are currently balancing
  uint8_t  balancingNum(void);
  // Whether no cells, some cells, or all cells are balancing
  uint8_t  balancingState(void);
  // Number of cells which are over voltage
  uint8_t  overVoltageNum(void);
  // Number of cells which are under voltage
  uint8_t  underVoltageNum(void);
  // Number of cells which are over temperature
  uint8_t  overTemperatureNum(void);
  // Cell slices - vectors of cell properties
  std::vector<uint16_t> millivoltsVect(void);
  std::vector<uint16_t> temperatureVect(void);
  std::vector<uint8_t>  balancingVect(void);
  std::vector<uint8_t>  overVoltageVect(void);
  std::vector<uint8_t>  underVoltageVect(void);
  std::vector<uint8_t>  overTemperatureVect(void);
  // Supporting class variables
  Stream & _Port;                       // Serial device
  uint8_t cellNum;                      // Number of cells
  std::vector<CellData> cellDataVect;   // Vector of CellData
  private:
  void                  generateMasterMessage(int16_t millivolts);
  void                  getSerialVector();
  CellData              extractCellData(uint8_t decodedArr[]);
  uint8_t               extractPayloadsToCellData(void );
  // Variables
  uint8_t               txData[CTMENCODEDPACKETSIZE];
  std::vector<uint8_t>  recievedSerialBytesVect;
};

#endif
