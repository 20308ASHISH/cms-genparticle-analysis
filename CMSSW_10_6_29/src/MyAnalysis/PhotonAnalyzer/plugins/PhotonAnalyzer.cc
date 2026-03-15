nclude <memory>
#include <vector>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"

class PhotonAnalyzer : public edm::EDAnalyzer {

public:
  explicit PhotonAnalyzer(const edm::ParameterSet&);
  ~PhotonAnalyzer(){}

private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  edm::EDGetTokenT<std::vector<reco::Photon>> photonToken_;
};

PhotonAnalyzer::PhotonAnalyzer(const edm::ParameterSet& iConfig)
{
  photonToken_ = consumes<std::vector<reco::Photon>>(
      iConfig.getParameter<edm::InputTag>("photons"));
}

void PhotonAnalyzer::analyze(const edm::Event& iEvent,
                             const edm::EventSetup& iSetup)
{

  edm::Handle<std::vector<reco::Photon>> photons;

  iEvent.getByToken(photonToken_, photons);

  std::cout << "Number of photons: " << photons->size() << std::endl;

  for (const auto& pho : *photons) {
    std::cout << "Photon pt = " << pho.pt()
              << " eta = " << pho.eta()
              << " phi = " << pho.phi()
              << std::endl;
  }
}

DEFINE_FWK_MODULE(PhotonAnalyzer);
