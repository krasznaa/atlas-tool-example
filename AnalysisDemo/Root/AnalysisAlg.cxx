// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "AnalysisDemo/AnalysisAlg.h"

// EDM include(s).
#include <xAODCore/ShallowCopy.h>

// Framework include(s).
#include <AsgDataHandles/ReadHandle.h>
#include <AsgDataHandles/WriteHandle.h>
#include <AsgMessaging/MessageCheck.h>
#include <AsgTools/CurrentContext.h>

namespace ATE {

StatusCode AnalysisAlg::initialize() {

    // Initialize the data handles.
    ANA_CHECK(m_inputMuons.initialize());
    ANA_CHECK(m_outputMuons.initialize());

    // Retrieve the calibration tool.
    ANA_CHECK(m_muonCalibratorTool.retrieve());

    // Return gracefully.
    return StatusCode::SUCCESS;
}

StatusCode AnalysisAlg::execute() {

    // Retrieve the input muons.
    SG::ReadHandle<xAOD::MuonContainer> inputMuonsHandle{m_inputMuons};

    // Make a shallow copy of the input muons.
    auto outputMuons = xAOD::shallowCopyContainer(
        *inputMuonsHandle, Gaudi::Hive::currentContext());

    // Calibrate the muons.
    ANA_CHECK(m_muonCalibratorTool->applyCalibration(*(outputMuons.first)));

    // Record the output muons into the event store.
    SG::WriteHandle<xAOD::MuonContainer> outputMuonsHandle{m_outputMuons};
    ANA_CHECK(outputMuonsHandle.record(std::move(outputMuons.first),
                                       std::move(outputMuons.second)));

    // Return gracefully.
    return StatusCode::SUCCESS;
}

}  // namespace ATE
