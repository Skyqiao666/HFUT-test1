#include "plotter.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
namespace auto_aim
{
Plotter::Plotter(std::string host, uint16_t port)
{
  socket_ = ::socket(AF_INET, SOCK_DGRAM, 0);

  destination_.sin_family = AF_INET;
  destination_.sin_port = ::htons(port);
  destination_.sin_addr.s_addr = ::inet_addr(host.c_str());

}  // namespace auto_aim
Plotter::~Plotter() { ::close(socket_); }

void Plotter::plot(const nlohmann :: json & json)
{
  auto data = json.dump();
  ::sendto(
    socket_, data.c_str(), data.length(), 0, reinterpret_cast<sockaddr *>(&destination_),
    sizeof(destination_));
}
}