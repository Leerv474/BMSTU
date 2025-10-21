export interface Phone {
  id: string;
  name: string;
  brand: string;
  price: number;
  image: string;
  description: string;
}

export const phones: Phone[] = [
  {
    id: "1",
    name: "iPhone 15 Pro",
    brand: "Apple",
    price: 1200,
    image: "https://via.placeholder.com/200x150?text=iPhone+15+Pro",
    description: "Очень крутое описание",
  },
  {
    id: "2",
    name: "Samsung Galaxy S24",
    brand: "Samsung",
    price: 1100,
    image: "https://via.placeholder.com/200x150?text=Galaxy+S24",
    description: "Очень крутое описание",
  },
  {
    id: "3",
    name: "Xiaomi 14",
    brand: "Xiaomi",
    price: 800,
    image: "https://via.placeholder.com/200x150?text=Xiaomi+14",
    description: "Очень крутое описание",
  },
];
