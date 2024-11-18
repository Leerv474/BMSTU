# CrowdStrike outage explained: What caused it and what’s next.

A CrowdStrike update caused a massive IT outage, crashing millions of Windows systems. Critical services and business operations were disrupted, revealing tech reliance risks.

What might be considered the largest IT outage in history was triggered by a botched software update from security vendor CrowdStrike, affecting millions of Windows systems around the world. Insurers estimate the outage will cost U.S. Fortune 500 companies $5.4 billion.

The outage occurred July 19, 2024, with millions of Windows systems failing and showing the infamous blue screen of death (BSOD).

CrowdStrike -- the company at the core of the outage -- is an endpoint security vendor whose primary technology is the Falcon platform, which helps protect systems against potential threats in a bid to minimize cybersecurity risks.

In many respects, the outage was a real manifestation of fears that computing users had at the end of the last century with the Y2K bug. With Y2K, the fear was that a bug in software systems would trigger widespread technology failures. While the CrowdStrike failure was not Y2K, it was a software issue that did, in fact, trigger massive disruption on a scale that has not been seen before.

## What caused the outage?

The CrowdStrike Falcon platform is widely used by organizations of all sizes across many industries. It is the pervasiveness of CrowdStrike's technology and its integration into so many mission-critical operations and industries that amplified the effect.

The outage was not a Microsoft Windows flaw directly, but rather a flaw in CrowdStrike Falcon that triggered the issue.

Falcon hooks into the Microsoft Windows OS as a Windows kernel process. The process has high privileges, giving Falcon the ability to monitor operations in real time across the OS. There was a logic flaw in Falcon sensor version 7.11 and above, causing it to crash. Due to CrowdStrike Falcon's tight integration into the Microsoft Windows kernel, it resulted in a Windows system crash and BSOD.

The flaw in CrowdStrike Falcon was inside of a sensor configuration update. The sensor is regularly updated -- sometimes multiple times daily -- to provide users with mitigation and threat protection.

The flawed update was contained in a file that CrowdStrike refers to as "channel files," which specifically provide configuration updates for behavioral protections. Channel file 291 is an update that was supposed to help improve how Falcon evaluates named pipe execution on Microsoft Windows. Named pipes are a common type of communication mechanism for interprocess communications on Microsoft Windows.

With channel file 291, CrowdStrike inadvertently introduced a logic error, causing the Falcon sensor to crash and, subsequently, Windows systems in which it was integrated.

The flaw isn't in all versions of channel file 291. The problematic version is channel file 291 (C-00000291\*.sys) with timestamp 2024-07-19 0409 UTC. Channel file 291 timestamped 2024-07-19 0527 UTC or later does not have the logic flaw. By that time, CrowdStrike had noticed its error and reverted the change. But, for many of its users, that reversion came too late as they had already updated, leading to BSOD and inoperable systems.

In terms of how the logic error was introduced into the Falcon sensor, the issue was a failure in the CrowdStrike development process. On July 24, 2024, the company issued a preliminary Post Incident Review (PIR). According to the PIR, there was a flaw in CrowdStrike's Content Validator component, used to check the integrity of rapid response content update. That flaw enabled the faulty version of channel file 291 to pass validation, even though it had an error.

On Aug. 6, CrowdStrike provided even more details on how the flaw was introduced, with a 12-page root cause analysis report. The report explained that part of the root cause was a mismatch between the number of input fields in the IPC (Inter-Process Communication) Template Type used for the channel file 291 update and the actual inputs provided by the sensor code. The IPC Template Type defined 21 input fields, but the sensor code only provided 20. A runtime array bounds check was missing in the Content Interpreter, and the Content Validator contained a logic error. The conditions that led to those errors were both patched by CrowdStrike after July 19, 2024. Bounds checking came into the system on July 25, 2024, while a patch that validates the number of actual inputs went into production July 27, 2024.

## How CrowdStrike aims to prevent future incidents

On Sept. 23, 2024, CrowdStrike testified in a U.S. House of Representatives hearing held by the House Subcommittee on Cybersecurity and Infrastructure Protection.

During the hearing, Adam Meyers, senior vice president of counter adversary operations at CrowdStrike, apologized to Congress for the outage. Meyers clarified the outage was not due to a cyberattack, but rather a result of a rapid response content update aimed at addressing new threats.

During his testimony, Meyers detailed how CrowdStrike has changed its content update procedures to prevent similar incidents in the future:

> Updates are now treated like code updates, with internal testing and phased implementation.
> A new "system of rings" approach for rolling out updates has been implemented.
> Customers can now choose their level of update adoption: early adopter, general availability or opt-out/delay.

## What services were affected?

Microsoft estimated that approximately 8.5 million Windows devices were directly affected by the CrowdStrike logic error flaw. That's less than 1% of Microsoft's global Windows install base.

But, despite the small percentage of the overall Windows install base, the systems affected were those running critical operations. Services affected include the following.

### Airlines and airports

The outage grounded thousands of flights worldwide, leading to significant delays and cancellations of more than 10,000 flights around the world. In the United States, affected airlines included Delta, United and American Airlines. These airlines were forced to cancel hundreds of flights until systems were restored. Globally, multiple airlines and airports were affected, including KLM, Porter Airlines, Toronto Pearson International Airport, Zurich Airport and Amsterdam Schiphol Airport.

### Public transit

Public transit in multiple cities was affected, including Chicago, Cincinnati, Minneapolis, New York City and Washington, D.C.

### Healthcare

Hospitals and healthcare clinics around the world faced significant disruptions in appointment systems, leading to delays and cancellations. Some states also reported 911 emergency services being affected, including Alaska, Indiana and New Hampshire.

### Financial services

Online banking systems and financial institutions around the world were affected by the outage. Multiple payment platforms were directly affected, and there were individuals who did not get their paychecks when expected.

### Media and broadcasting

Multiple media and broadcast outlets around the world, including British broadcaster Sky News, were taken off the air by the outage.

## Legal fallout

In the aftermath of the CrowdStrike incident there has been some legal fallout, including the following:

### Shareholder class action lawsuit

The lawsuit alleges CrowdStrike made false and misleading statements about the adequacy of its software testing procedures. The suit claims the CrowdStrike share price declined after the incident. As a result, the class action suit is looking for damages on behalf of investors who held CrowdStrike shares between Nov. 29, 2023, and July 29, 2024.

### Delta Air Lines lawsuit

Delta Air Lines filed a lawsuit against CrowdStrike on Oct. 25, 2024, over the outage that grounded thousands of flights and cost the airline approximately $500 million. Delta accuses the cybersecurity firm of negligence and causing a catastrophe. While Delta was not the only airline affected by this global IT outage, it was slower than other airlines to recover.

In response to this lawsuit, CrowdStrike sued Delta, saying they were not responsible for the mass flight cancellations. In the suit, CrowdStrike said any damages Delta suffered after the outage was primarily the result of "Delta's own negligence."

## Why Apple and Linux were not affected

CrowdStrike's software doesn't just run on Microsoft Windows; it also runs on Apple's macOS and the Linux OS.

But the July outage only affected Microsoft Windows. The root cause of the outage was a faulty sensor configuration update that specifically affected Windows systems. The channel file 291 update was never issued to macOS or Linux systems as the update deals with named pipe execution that only occurs on the Microsoft Windows OS.

The way that the Falcon sensor integrates as a Windows kernel process is also not the same in macOS or Linux. Those OSes have different integration points to limit potential risk.

However, there was a reported incident in June from Linux vendor Red Hat, where the Falcon sensor -- running as an eBPF program in Linux -- triggered a kernel panic. In Linux, a kernel panic is a type of crash, though typically not as dramatic as BSOD. That issue was resolved without Red Hat reporting any major incidents.

## How long will it take businesses to recover from this outage?

CrowdStrike itself was able to identify and deploy a fix for the issue in 79 minutes. While CrowdStrike quickly identified and deployed a fix for the issue, the recovery process for businesses is complex and time-consuming. Among the issues is that, once the problematic update was installed, the underlying Windows OS would trigger BSOD, rendering the system inoperative using the normal boot process.

IT administrators had to manually boot affected systems into Safe Mode or the Windows Recovery Environment to delete the problematic channel file 291 and restore normal operations. That process is labor-intensive, especially for organizations with many affected devices. In some cases, the process also required physical access to each machine, adding further time and effort to the process.

Some businesses were able to apply the fix within a few days. However, the process was not straightforward for all, particularly those with extensive IT infrastructure and encrypted drives. The use of the Microsoft Windows BitLocker encryption technology by some organizations made it significantly more time-consuming to recover as BitLocker recovery keys were required.

It was initially estimated that it could potentially take months for some organizations to entirely recover all affected systems from the outage. As of July 29, 2024, CrowdStrike reported that approximately 99% of affected Windows sensors were back online.

## Hackers take advantage of outage

While the outage was not due to a cyberattack, threat actors have taken advantage of the incident.

According to a blog post from CrowdStrike, the security vendor has received reports of the following malicious activity:

Phishing emails sent to customers posing as CrowdStrike support. Fake phone calls impersonating CrowdStrike staff. Selling scripts claiming to automate recovery from the botched update. Posing as independent researchers saying the outage was due to a cyberattack and offering remediation insights.

CISA urges individuals and organizations to only follow instructions from legitimate sources and avoid opening suspicious emails and links.

## How can businesses be better prepared for tech outages?

The CrowdStrike Windows outage highlighted the vulnerabilities of modern society's heavy reliance on technology. While system backups and automated processes are essential, having manual procedures in place can significantly enhance business continuity during tech outages.
