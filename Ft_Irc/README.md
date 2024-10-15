# 개요
 C++를 사용하여 IRC 서버를 개발한 프로젝트입니다. 
 멀티스레드를 사용하지 않았지만 non-blocking 방식을 사용하여 수신 및 응답에 있어서 막힘이 없도록 구현했습니다. 
 해당 프로젝트는 RFC 1459 컨벤션에 맞추어 코드를 작성되었습니다. 
 
 IRC 서버를 사용해서 클라이언트가 사용할 수 있는 기능은 다음과 같습니다. 
- KICK - Eject a client from the channel
- INVITE - Invite a client to a channel
- TOPIC - Change or view the channel topic
- MODE - Change the channel’s mode:
  - i: Set/remove Invite-only channel
  - t: Set/remove the restrictions of the TOPIC command to channel
      operators
  - k: Set/remove the channel key (password)
  - o: Give/take channel operator privilege
# 실행방법
```Bash
make docker
docker logs [docker ID]
// 서버의 IP, Port, Password 확인
```
위와 같이 서버를 동작시키고, 다른 클라이언트를 설치하여 `/connect [IP] [Port] [Password]`를 사용하여 접속합니다.
# 시연
![Irc-시연](https://github.com/user-attachments/assets/0491fc2a-f1ea-4ddd-bf2b-cd92c7f3d30e)
