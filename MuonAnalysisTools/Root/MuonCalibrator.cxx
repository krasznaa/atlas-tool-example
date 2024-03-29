// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "MuonAnalysisTools/MuonCalibrator.h"

// System include(s).
#include <cmath>
#include <stdexcept>

namespace ATE {

MuonCalibrator::MuonCalibrator(const std::string& name)
    : asg::AsgMessaging(name), m_name(name) {}

MuonCalibrator::MuonCalibrator(const MuonCalibrator& parent)
    : asg::AsgMessaging(parent.m_name),
      m_affectingSystematics(parent.m_affectingSystematics),
      m_recommendedSystematics(parent.m_recommendedSystematics),
      m_nominal(parent.m_nominal),
      m_foo(parent.m_foo),
      m_bar(parent.m_bar) {}

MuonCalibrator::MuonCalibrator(MuonCalibrator&& parent)
    : asg::AsgMessaging(parent.m_name),
      m_affectingSystematics(std::move(parent.m_affectingSystematics)),
      m_recommendedSystematics(std::move(parent.m_recommendedSystematics)),
      m_nominal(std::move(parent.m_nominal)),
      m_foo(std::move(parent.m_foo)),
      m_bar(std::move(parent.m_bar)) {}

StatusCode MuonCalibrator::initialize() {

    // Tell the user what's happening.
    ATH_MSG_INFO("Initializing the EDM-less muon calibrator");

    // Set up the systematic variations.
    m_recommendedSystematics = {{"MUON_FOO", 1}, {"MUON_FOO", -1}};
    m_affectingSystematics = m_recommendedSystematics;
    m_affectingSystematics.insert(m_affectingSystematics.end(),
                                  {{"MUON_BAR", 1}, {"MUON_BAR", -1}});

    // Set up the calibration data.
    m_nominal.push_back({-5.f, 5.f, -M_PI, M_PI, 0.f, 1e10f, 0.f});

    m_foo.push_back({-5.f, 0.f, -M_PI, M_PI, 0.f, 1e5f, 0.1f});
    m_foo.push_back({0.f, 5.f, -M_PI, M_PI, 0.f, 1e5f, 0.05f});
    m_foo.push_back({-5.f, 5.f, -M_PI, M_PI, 0.f, 1e10f, 0.03f});

    m_bar.push_back({-5.f, 5.f, -M_PI, M_PI, 0.f, 1e5f, 0.1f});
    m_bar.push_back({-5.f, 5.f, -M_PI, M_PI, 0.f, 1e10f, 0.2f});

    // Return gracefully.
    return StatusCode::SUCCESS;
}

CP::SystematicSet MuonCalibrator::affectingSystematics() const {

    return m_affectingSystematics;
}

CP::SystematicSet MuonCalibrator::recommendedSystematics() const {

    return m_recommendedSystematics;
}

float MuonCalibrator::getCalibratedPt(float pt, float eta, float phi,
                                      const CP::SystematicSet& syst) const {

    // Get phi into the -pi to pi range. Apparently reconstructed muons still
    // have values outside of it sometimes. :-/
    while (phi < -M_PI) {
        phi += 2.f * M_PI;
    }
    while (phi >= M_PI) {
        phi -= 2.f * M_PI;
    }

    /// Lambda checking if a muon falls in a specific @c CalibData range.
    auto in_range = [eta, phi](const CalibData& calib, float pt) -> bool {
        return (calib.min_eta <= eta && eta < calib.max_eta &&
                calib.min_phi <= phi && phi < calib.max_phi &&
                calib.min_pt <= pt && pt < calib.max_pt);
    };

    /// Lambda applying a calibration to a muon.
    auto apply_calib = [&in_range, &pt, eta, phi](
                           const std::vector<CalibData>& calibs,
                           auto operation) -> void {
        for (const auto& calib : calibs) {
            if (in_range(calib, pt)) {
                pt = operation(pt, calib.variation);
                return;
            }
        }
        throw std::out_of_range("Muon out of range for calibration");
    };

    // First, apply the "nominal calibration".
    apply_calib(m_nominal, [](float pt, float variation) {
        return pt * (1.f + variation);
    });

    // Then, apply the systematic variation(s).
    if (syst.find({"MUON_FOO", 1}) != syst.end()) {
        apply_calib(m_foo, [](float pt, float variation) {
            return pt * (1.f + variation);
        });
    }
    if (syst.find({"MUON_FOO", -1}) != syst.end()) {
        apply_calib(m_foo, [](float pt, float variation) {
            return pt * (1.f - variation);
        });
    }
    if (syst.find({"MUON_BAR", 1}) != syst.end()) {
        apply_calib(m_bar, [](float pt, float variation) {
            return pt * (1.f + variation);
        });
    }
    if (syst.find({"MUON_BAR", -1}) != syst.end()) {
        apply_calib(m_bar, [](float pt, float variation) {
            return pt * (1.f - variation);
        });
    }

    // Return the "calibrated" transverse momentum.
    return pt;
}

}  // namespace ATE
