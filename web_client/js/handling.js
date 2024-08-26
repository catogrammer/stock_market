// Function to handle form submission
function handleFormSubmit(event) {
    event.preventDefault(); // Prevent default form submission

    const form = event.target;

    if (validateForm(form)) {
        const crypto = form.querySelector('#crypto').value;
        const quantity = form.querySelector('#quantity').value;
        const orderType = form.querySelector('#orderType').value;
        const price = form.querySelector('#price').value;
        const paymentMethod = form.querySelector('#paymentMethod').value;
        const walletAddress = form.querySelector('#walletAddress').value;

        alert(`Order placed successfully! \n\nCrypto: ${crypto} \nQuantity: ${quantity} \nOrder Type: ${orderType} \nPrice: ${price} \nPayment Method: ${paymentMethod} \nWallet Address: ${walletAddress}`);

        form.reset(); // Optionally, reset the form
    }
}
