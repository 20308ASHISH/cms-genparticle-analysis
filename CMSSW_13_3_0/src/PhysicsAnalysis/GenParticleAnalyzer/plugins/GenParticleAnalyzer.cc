#include <memory>
#include <vector>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TH1F.h"

class GenParticleAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources> {

public:
  explicit GenParticleAnalyzer(const edm::ParameterSet&);
  ~GenParticleAnalyzer() override {}

private:
  void analyze(const edm::Event&, const edm::EventSetup&) override;

  edm::EDGetTokenT<std::vector<reco::GenParticle>> genParticlesToken_;

  TH1F* h_A_pt;
  TH1F* h_A_eta;
  TH1F* h_A_phi;
  TH1F* h_A_energy;	

  TH1F* h_gamma_pt;
  TH1F* h_gamma_eta;
  TH1F* h_gamma_phi;
};

GenParticleAnalyzer::GenParticleAnalyzer(const edm::ParameterSet& iConfig)
{
  usesResource("TFileService");

  genParticlesToken_ =
      consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticles"));

  edm::Service<TFileService> fs;

  // A particle histograms
  h_A_pt  = fs->make<TH1F>("A_pt","A pT",100,0,200);
  h_A_eta = fs->make<TH1F>("A_eta","A eta",100,-5,5);
  h_A_phi = fs->make<TH1F>("A_phi","A phi",100,-3.2,3.2);
  h_A_energy = fs->make<TH1F>("A_energy","A Energy",100,0,500);

  // photon histograms
  h_gamma_pt  = fs->make<TH1F>("gamma_pt","Photon pT",100,0,200);
  h_gamma_eta = fs->make<TH1F>("gamma_eta","Photon eta",100,-5,5);
  h_gamma_phi = fs->make<TH1F>("gamma_phi","Photon phi",100,-3.2,3.2);
}

void GenParticleAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup&)
{
  edm::Handle<std::vector<reco::GenParticle>> genParticles;
  iEvent.getByToken(genParticlesToken_, genParticles);

  for (const auto& p : *genParticles) {

    int pdg = p.pdgId();

    // A particle
    if (abs(pdg) == 36) {
      h_A_pt->Fill(p.pt());
      h_A_eta->Fill(p.eta());
      h_A_phi->Fill(p.phi());
      h_A_energy->Fill(p.energy());
    }

    // photons from A decay
    if (pdg == 22 && p.mother() && abs(p.mother()->pdgId()) == 36) {
      h_gamma_pt->Fill(p.pt());
      h_gamma_eta->Fill(p.eta());
      h_gamma_phi->Fill(p.phi());
    }
  }
}

DEFINE_FWK_MODULE(GenParticleAnalyzer);
