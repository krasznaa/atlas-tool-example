// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#ifndef ANALYSISDEMO_ANALYSISALG_H
#define ANALYSISDEMO_ANALYSISALG_H

// Project include(s).
#include "MuonAnalysisTools/IMuonCalibratorTool.h"

// EDM include(s).
#include <xAODMuon/MuonContainer.h>

// Framework include(s).
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <AsgDataHandles/ReadHandleKey.h>
#include <AsgDataHandles/WriteHandleKey.h>
#include <AsgTools/ToolHandle.h>

namespace ATE {

/// Algorithm demonstrating the usage of @c ATE::IMuonCalibrationTool
///
/// This algorithm demonstrates the usage of the @c ATE::IMuonCalibrationTool
/// interface. It retrieves a muon container from the input, creates a
/// shallow copy of it, and writes the calibrated muons into the event store.
///
class AnalysisAlg : public EL::AnaAlgorithm {

public:
    // Inherit the base class's constructor(s).
    using EL::AnaAlgorithm::AnaAlgorithm;

    /// @name Functions implementing the EL::Algorithm interface
    /// @{

    /// Function called at the beginning of the job
    StatusCode initialize() override;
    /// Function executing the algorithm
    StatusCode execute() override;

    /// @}

private:
    /// Input muon container
    SG::ReadHandleKey<xAOD::MuonContainer> m_inputMuons{
        this, "InputMuons", "Muons", "Input muon container"};
    /// Output muon container
    SG::WriteHandleKey<xAOD::MuonContainer> m_outputMuons{
        this, "OutputMuons", "AnalysisMuons", "Output muon container"};

    /// Tool performing the muon momentum calibration
    ToolHandle<IMuonCalibratorTool> m_muonCalibratorTool{
        this, "MuonCalibratorTool", "ATE::MuonCalibratorTool/CalibratorTool",
        "Tool performing the muon momentum calibration"};

};  // class AnalysisAlg

}  // namespace ATE

#endif  // ANALYSISDEMO_ANALYSISALG_H
