// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "MuonAnalysisTools/MuonCalibratorRDF.h"

// System include(s).
#include <stdexcept>

namespace ATE::RDF {

std::vector<float> MuonCalibrator::operator()(
    const std::vector<float>& pt, const std::vector<float>& eta,
    const std::vector<float>& phi) const {

    // Do some sanity checks.
    if ((pt.size() != eta.size()) || (pt.size() != phi.size())) {
        throw std::invalid_argument("Muon vectors have different sizes");
    }

    // Create the output vector.
    std::vector<float> result;
    result.reserve(pt.size());

    // Fill it.
    for (size_t i = 0; i < pt.size(); ++i) {
        result.push_back(getCalibratedPt(pt[i], eta[i], phi[i]));
    }

    // Return it.
    return result;
}

std::vector<float> MuonCalibratorxAOD::operator()(
    const xAOD::MuonContainer& muons) const {

    // Create the output vector.
    std::vector<float> result;
    result.reserve(muons.size());

    // Fill it.
    for (const xAOD::Muon* muon : muons) {
        result.push_back(getCalibratedPt(muon->pt(), muon->eta(), muon->phi()));
    }

    // Return it.
    return result;
}

ROOT::RVec<std::vector<float> > MuonVariator::operator()(
    const std::vector<float>& pt, const std::vector<float>& eta,
    const std::vector<float>& phi) const {

    // Do some sanity checks.
    if ((pt.size() != eta.size()) || (pt.size() != phi.size())) {
        throw std::invalid_argument("Muon vectors have different sizes");
    }

    // Create the output vector.
    ROOT::RVec<std::vector<float> > result;
    result.resize(m_recommendedSystematics.size());

    // Fill it.
    auto syst_it = m_recommendedSystematics.begin();
    auto syst_end = m_recommendedSystematics.end();
    for (std::size_t i = 0; syst_it != syst_end; ++i, ++syst_it) {
        result[i].reserve(pt.size());
        for (std::size_t j = 0; j < pt.size(); ++j) {
            result[i].push_back(
                getCalibratedPt(pt[j], eta[i], phi[i], {*syst_it}));
        }
    }

    // Return it.
    return result;
}

ROOT::RVec<std::vector<float> > MuonVariatorxAOD::operator()(
    const xAOD::MuonContainer& muons) const {

    // Create the output vector.
    ROOT::RVec<std::vector<float> > result;
    result.resize(m_recommendedSystematics.size());

    // Fill it.
    auto syst_it = m_recommendedSystematics.begin();
    auto syst_end = m_recommendedSystematics.end();
    for (std::size_t i = 0; syst_it != syst_end; ++i, ++syst_it) {
        result[i].reserve(muons.size());
        for (const xAOD::Muon* muon : muons) {
            result[i].push_back(getCalibratedPt(muon->pt(), muon->eta(),
                                                muon->phi(), {*syst_it}));
        }
    }

    // Return it.
    return result;
}

}  // namespace ATE::RDF
