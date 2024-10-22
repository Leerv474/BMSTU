package ru.bmstu.product;

import lombok.AllArgsConstructor;

import java.util.List;

@AllArgsConstructor
public class ProductService {
    private List<Product> products;

    public void filterProducts(double minPrice) {
        products.stream().filter(product -> product.getPrice() > minPrice && product.getQuantity() > 0)
                .forEach(product -> System.out.println(product.getName()));
    }
}
