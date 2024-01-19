// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#ifndef MUONANALYSISTOOLS_MUONCALIBRATORTOOL_H
#define MUONANALYSISTOOLS_MUONCALIBRATORTOOL_H

// Local include(s).
#include "MuonAnalysisTools/IMuonCalibratorTool.h"
#include "MuonAnalysisTools/MuonCalibrator.h"

// Framework include(s).
#include <AsgTools/AsgTool.h>
#include <PATInterfaces/ISystematicsTool.h>
#include <PATInterfaces/SystematicSet.h>
#include <PATInterfaces/SystematicsTool.h>

// System include(s).
#include <string>

namespace ATE {

/// Tool implementing the @c ATE::IMuonCalibratorTool interface
class MuonCalibratorTool : public virtual IMuonCalibratorTool,
                           public asg::AsgTool,
                           public CP::SystematicsTool {

public:
    /// Create proper constructor(s) for Athena
    ASG_TOOL_CLASS(MuonCalibratorTool, ATE::IMuonCalibratorTool)

    /// Constructor for standalone usage
    MuonCalibratorTool(const std::string &name);

    /// @name Functions implementing @c asg::AsgTool functions
    /// @{

    /// Initialize the tool
    StatusCode initialize() override;

    /// @}

    /// @name Functions implementing the @c ATE::IMuonCalibratorTool interface
    /// @{

    /// Apply the calibration for a single muon
    CP::CorrectionCode applyCalibration(xAOD::Muon &muon) const override;
    /// Apply the calibration for a container of muons
    CP::CorrectionCode applyCalibration(
        xAOD::MuonContainer &muons) const override;

    /// @}

private:
    /// @name Functions implementing the @c CP::SystematicsTool interface
    /// @{

    /// Configure the tool for a given set of systematic variations
    StatusCode sysApplySystematicVariation(
        const CP::SystematicSet &systConfig) override;

    /// @}

    /// The active systematic variation(s) to apply
    CP::SystematicSet m_syst;
    /// Tool performing the actual calibration
    MuonCalibrator m_calibrator;

};  // class MuonCalibratorTool

}  // namespace ATE

#endif  // MUONANALYSISTOOLS_MUONCALIBRATORTOOL_H
