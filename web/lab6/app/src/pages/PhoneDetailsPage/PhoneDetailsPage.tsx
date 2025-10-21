import { useParams } from "react-router-dom";
import { phones } from "../../data/phoneData";

export const PhoneDetails = () => {
  const { id } = useParams<{ id: string }>();
  const phone = phones.find((p) => p.id === id);

  if (!phone) return <p>Телефон не найден.</p>;

  return (
    <div>
      <h2>{phone.name}</h2>
      <img src={phone.image} alt={phone.name} />
      <p><strong>Бренд:</strong> {phone.brand}</p>
      <p><strong>Цена:</strong> {phone.price}$</p>
      <p>{phone.description}</p>
    </div>
  );
};
