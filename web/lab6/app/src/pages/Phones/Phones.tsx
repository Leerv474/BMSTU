
import { Link } from "react-router-dom";
import { phones } from "../../data/phoneData";

export const Phones = () => {
  return (
    <div>
      <h2>Телефоны</h2>
      <ul>
        {phones.map((phone) => (
          <li key={phone.id}>
            <Link to={`/phones/${phone.id}`}>{phone.name}</Link>
          </li>
        ))}
      </ul>
    </div>
  );
};
