import { Link } from "react-router-dom";
import { useState } from "react";
import "./Navbar.css";

export const Navbar = () => {
  const [isShopOpen, setIsShopOpen] = useState<boolean>(false);

  const toggleShopMenu = () => {
    setIsShopOpen((prev) => !prev);
  };

  return (
    <nav className="navbar">
      <ul>
        <li><Link to="/">Главная</Link></li>
        <li><Link to="/about">О нас</Link></li>

        <li className="dropdown">
          <button className="dropdown-btn" onClick={toggleShopMenu}>
            Магазин {isShopOpen ? "▲" : "▼"}
          </button>
          {isShopOpen && (
            <ul className="submenu">
              <li><Link to="/phones">Телефоны</Link></li>
            </ul>
          )}
        </li>

        <li><Link to="/contacts">Контакты</Link></li>
      </ul>
    </nav>
  );
};

