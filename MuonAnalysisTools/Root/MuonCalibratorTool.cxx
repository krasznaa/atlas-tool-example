// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "MuonAnalysisTools/MuonCalibratorTool.h"

// Framework include(s).
#include <AsgMessaging/MessageCheck.h>

// System include(s).
#include <stdexcept>

namespace ATE {

MuonCalibratorTool::MuonCalibratorTool(const std::string &name)
    : asg::AsgTool(name), m_calibrator(this->name()) {}

StatusCode MuonCalibratorTool::initialize() {

    // Tell the user what's happening.
    ATH_MSG_INFO("Initializing the dual-use muon calibrator tool");

    // Initialize the underlying tool.
    ANA_CHECK(m_calibrator.initialize());

    // Set up the base class(es).
    addAffectingSystematics(m_calibrator.affectingSystematics());
    ANA_CHECK(addRecommendedSystematics(m_calibrator.recommendedSystematics()));

    // Return gracefully.
    return StatusCode::SUCCESS;
}

CP::CorrectionCode MuonCalibratorTool::applyCalibration(
    xAOD::Muon &muon) const {

    // Check for errors during the calibration. Only looking for out of range
    // errors. Everything else is allowed to make its way to a higher level.
    try {
        // Set the calibrated transverse momentum on the muon.
        muon.setP4(m_calibrator.getCalibratedPt(muon.pt(), muon.eta(),
                                                muon.phi(), m_syst),
                   muon.eta(), muon.phi());
    } catch (const std::out_of_range &) {
        ATH_MSG_WARNING("Muon is outside of validity range: "
                        << "pt = " << muon.pt() << ", "
                        << "eta = " << muon.eta() << ", "
                        << "phi = " << muon.phi());
        return CP::CorrectionCode::OutOfValidityRange;
    }

    // Return gracefully.
    return CP::CorrectionCode::Ok;
}

CP::CorrectionCode MuonCalibratorTool::applyCalibration(
    xAOD::MuonContainer &muons) const {

    // Make the helper macro(s) work correctly.
    ANA_CHECK_SET_TYPE(CP::CorrectionCode);

    // Perform the calibration for each muon in the container.
    for (xAOD::Muon *muon : muons) {
        ANA_CHECK(applyCalibration(*muon));
    }

    // Return gracefully.
    return CP::CorrectionCode::Ok;
}

StatusCode MuonCalibratorTool::sysApplySystematicVariation(
    const CP::SystematicSet &syst) {

    // Remember the active systematic variation(s).
    m_syst = syst;
    return StatusCode::SUCCESS;
}

}  // namespace ATE
