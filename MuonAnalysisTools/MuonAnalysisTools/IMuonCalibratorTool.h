// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#ifndef MUONANALYSISTOOLS_IMUONCALIBRATORTOOL_H
#define MUONANALYSISTOOLS_IMUONCALIBRATORTOOL_H

// Framework include(s).
#include <AsgTools/IAsgTool.h>
#include <PATInterfaces/CorrectionCode.h>

// EDM include(s).
#include <xAODMuon/Muon.h>
#include <xAODMuon/MuonContainer.h>

/// Namespace for all code in the example project
namespace ATE {

/// Interface for the muon calibration tool(s)
class IMuonCalibratorTool : virtual public asg::IAsgTool {

    /// Declare the interface that the class provides
    ASG_TOOL_INTERFACE(ATE::IMuonCalibratorTool)

public:
    /// Apply the calibration for a single muon
    virtual CP::CorrectionCode applyCalibration(xAOD::Muon &muon) const = 0;
    /// Apply the calibration for a container of muons
    virtual CP::CorrectionCode applyCalibration(
        xAOD::MuonContainer &muons) const = 0;

};  // class IMuonCalibratorTool

}  // namespace ATE

#endif  // MUONANALYSISTOOLS_IMUONCALIBRATORTOOL_H