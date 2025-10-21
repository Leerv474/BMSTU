import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { Navbar } from "./components/Navbar";
import { Home } from "./pages/HomePage/HomePage";
import { About } from "./pages/AboutPage/AboutPage";
import { Contacts } from "./pages/ContactsPage/ContactsPage";
import { Phones } from "./pages/Phones/Phones";
import { PhoneDetails } from "./pages/PhoneDetailsPage/PhoneDetailsPage";

function App() {
  return (
    <Router>
      <Navbar />
      <div style={{ padding: "20px" }}>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/about" element={<About />} />
          <Route path="/contacts" element={<Contacts />} />
          <Route path="/phones" element={<Phones />} />
          <Route path="/phones/:id" element={<PhoneDetails />} />
        </Routes>
      </div>
    </Router>
  );
}

export default App;

