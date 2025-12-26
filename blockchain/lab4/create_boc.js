import { 
  beginCell, 
  toNano, 
  Cell 
} from "ton";
import { WalletContractV3R2 } from "ton";
import { NFTCollection } from "ton-nft"; // or your SDK that supports minting

// Example: mint payload
const collectionAddress = "EQ...";  // your deployed collection
const ownerAddress = "EQBUI264Vxn-MtRYrh7RlZTJkKj58B77kibcvoyojpskJP2u";       // your wallet
const contentUri = "https://raw.githubusercontent.com/Leerv474/BMSTU/refs/heads/master/blockchain/lab4/metadata.json";

// Create NFTItem cell
const nftItemCell = new Cell();
// encode owner + content URI properly
// ... SDK-specific code here ...

const boc = nftItemCell.toBoc();  // This is your mint BOC
