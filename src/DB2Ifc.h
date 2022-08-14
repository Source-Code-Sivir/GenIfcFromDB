#pragma once
#ifndef DB2IFC_H
#define DB2IFC_H
#include<unordered_map>
#include<memory>
#include"ifcpp\IFC4\include\IfcReinforcingBar.h"
#include"ifcpp\IFC4\include\IfcCompositeCurve.h"
#include "ifcpp\IFC4\include\IfcReinforcingBarType.h"
#include "ifcpp\IFC4\include\IfcReinforcingBarTypeEnum.h"
#include "ifcpp\IFC4\include\IfcTransitionCode.h"
#include "ifcpp\IFC4\include\IfcTrimmingSelect.h"
#include "ifcpp\IFC4\include\IfcTrimmingPreference.h"
#include "ifcpp\IFC4\include\IfcLine.h"
#include "ifcpp\IFC4\include\IfcVector.h"
#include "ifcpp/IFC4/include/IfcGloballyUniqueId.h"
#include "ifcpp/IFC4/include/IfcOwnerHistory.h"
#include "ifcpp/IFC4/include/IfcText.h"
#include "ifcpp/IFC4/include/IfcAreaMeasure.h"
#include "ifcpp/IFC4/include/IfcVolumeMeasure.h"
#include "ifcpp/IFC4/include/IfcPlaneAngleMeasure.h"
#include "ifcpp/IFC4/include/IfcSolidAngleMeasure.h"
#include "ifcpp/IFC4/include/IfcTimeMeasure.h"
#include "ifcpp/IFC4/include/IfcMassMeasure.h"
#include "ifcpp/IFC4/include/IfcThermodynamicTemperatureMeasure.h"
#include "ifcpp/IFC4/include/IfcLuminousIntensityMeasure.h"
#include "ifcpp\IFC4\include\IfcDerivedUnitEnum.h"
#include "ifcpp\IFC4\include\IfcVolumetricFlowRateMeasure.h"
#include "ifcpp\IFC4\include\IfcGeometricProjectionEnum.h"
#include "ifcpp\IFC4\include\IfcProfileTypeEnum.h"
#include "ifcpp\IFC4\include\IfcReflectanceMethodEnum.h"
#include "ifcpp\IFC4\include\IfcSurfaceSide.h"
#include"ifcpp/IFC4\include\IfcCompositeCurveSegment.h"
#include"ifcpp/IFC4\include\IfcBoolean.h"
#include"ifcpp\IFC4\include\IfcTrimmedCurve.h"
#include"ifcpp\IFC4\include\IfcParameterValue.h"
#include"ifcpp\IFC4\include\IfcCartesianPoint.h"
#include"ifcpp\IFC4\include\IfcLengthMeasure.h"
#include"ifcpp\IFC4\include\IfcVector.h"
#include"ifcpp\IFC4\include\IfcDirection.h"
#include"ifcpp\IFC4\include\IfcReal.h"
#include"ifcpp\IFC4\include\IfcCircle.h"
#include"ifcpp\IFC4\include\IfcPositiveLengthMeasure.h"
#include"ifcpp\IFC4\include\IfcAxis2Placement3D.h"
#include"ifcpp\IFC4\include\IfcAxis2Placement.h"
#include"ifcpp\IFC4\include\IfcDirection.h"
#include"ifcpp\IFC4\include\IfcRepresentationMap.h"
#include"ifcpp\IFC4\include\IfcRepresentation.h"
#include"ifcpp\IFC4\include\IfcSweptDiskSolid.h"
#include"ifcpp\IFC4\include\IfcShapeRepresentation.h"
#include"ifcpp\IFC4\include\IfcTrimmingPreference.h"
#include"ifcpp\IFC4\include\IfcGeometricRepresentationContext.h"
#include"ifcpp\IFC4\include\IfcMappedItem.h"
#include"ifcpp\IFC4\include\IfcCartesianTransformationOperator.h"
#include"ifcpp\IFC4\include\IfcProductDefinitionShape.h"
#include"ifcpp\IFC4\include\IfcLocalPlacement.h"
#include"ifcpp\IFC4\include\IfcLogical.h"
#include"ifcpp\IFC4\include\IfcIdentifier.h"
#include"ifcpp\IFC4\include\IfcLabel.h"
#include"ifcpp\IFC4\include\IfcBuildingStorey.h"
#include"ifcpp\IFC4\include\IfcBuilding.h"
#include"ifcpp\IFC4\include\IfcSite.h"
#include"ifcpp\IFC4\include\IfcExtrudedAreaSolid.h"
#include"ifcpp\IFC4\include\IfcBeam.h"
#include"ifcpp\IFC4\include\IfcRelContainedInSpatialStructure.h"
#include"ifcpp\IFC4\include\IfcStyledItem.h"
#include"ifcpp\IFC4\include\IfcPresentationStyleAssignment.h"
#include"ifcpp\IFC4\include\IfcNormalisedRatioMeasure.h"
#include"ifcpp\IFC4\include\IfcElementAssembly.h"

//#include"ifcpp\IFC4\include\IfcShapeRepresentationItem.h"

int GenIfcPoint_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcDirection_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcPlacement3D_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcLines_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcCircles_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcTrimmedCurve_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcCompositeCurve_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcSweptDiskSolid_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcMappedItem_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcReinforcingBar_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcLocalPlacement_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcBeam_callback(void* data, int argc, char** argv, char** azColName);
int GenIfcExtrudedAreaSolid_callback(void* data, int argc, char** argv, char** azColName);
class DB2Ifc {
public:
	static std::unordered_map<int ,std::shared_ptr<IfcCartesianPoint>> points;
	static std::unordered_map<int, std::shared_ptr<IfcDirection>> directions;
	static std::unordered_map<int, std::shared_ptr<IfcAxis2Placement3D>>placements;
	static std::unordered_map<int, std::shared_ptr<IfcLine>>lines;
	static std::unordered_map<int, std::shared_ptr<IfcCircle>>circles;
	static std::unordered_map<int, std::shared_ptr<IfcTrimmedCurve>>TrimmedCurves;
	static std::unordered_map<int, std::shared_ptr<IfcCompositeCurve>>CompositeCurves;
	static std::unordered_map<int, std::shared_ptr<IfcSweptDiskSolid>>SweptDIskSolids;
	static std::unordered_map<int, std::shared_ptr<IfcMappedItem>>MappedItems;
	static std::unordered_map<int, std::shared_ptr<IfcReinforcingBar>>ReinforcingBars;
	static std::unordered_map<int, std::shared_ptr<IfcLocalPlacement>>LocalPlacements;
	static std::unordered_map<int, std::shared_ptr<IfcBuilding>>Buildings;
	static std::unordered_map<int, std::shared_ptr<IfcBuildingStorey>>BuildingStorey;
	static std::unordered_map<int, std::shared_ptr<IfcExtrudedAreaSolid>> ExtrudedAreaSolids;
	static std::unordered_map<int, std::shared_ptr<IfcBeam>> beams;

	static std::unordered_map<int, std::shared_ptr<IfcRelContainedInSpatialStructure>> storeyComponents;//层所有的ifc实体 里面是IfcrealAgg


	static std::unordered_map<int, std::shared_ptr<IfcRelAggregates>> BeamBarAssembly;

	static shared_ptr<IfcRelAggregates> buildingAggregates;

	//static std::unordered_map<int, std::shared_ptr<IfcProfileDef>> ProfileDefs;
	static DB2Ifc* ins;
	static std::vector<shared_ptr<BuildingEntity>>vec_new_entitys;
	static DB2Ifc* Instance() {
		if (ins == nullptr) {
			ins = new DB2Ifc();
		}
		return ins;
	}
	static void GenPointsFromDB();
	static void GenDirectionsFromDB();
	static void GenPlacements3DFromDB();
	static void GenLinesFromDB();
	static void GenCirclesFromDB();
	static void GenTrimmedCurveFromDB();
	static void GenCompositeCurveFromDB();
	static void GenSweptDiskSoldFromDB();
	static void GenMappedItemFromDB();
	static void GenReinforcingBarFromDB();
	static void GenAllFromDB();
	static void GenLocalPlacementFromDB();
	static void GenBuildingFromDB();
	static void GenBuildingStoreyFromDB();
	static void GenBeamFromDB();
	static void GenExtrudedAreaSolidFromDB();
	static shared_ptr<IfcSite> site;
	static shared_ptr<IfcPresentationStyleAssignment> mainBarColor;
	static shared_ptr<IfcPresentationStyleAssignment> tiedBarColor;
	static shared_ptr<IfcPresentationStyleAssignment> shearBarColor;
	static shared_ptr<IfcPresentationStyleAssignment> waistBarColor;
private:
	DB2Ifc();
	~DB2Ifc() {};
};
#endif // !DB2IFC_H

